/****************************************************************************

getopt.c - Read command line options

AUTHOR: Gregory Pietsch
CREATED Fri Jan 10 21:13:05 1997

DESCRIPTION:

The getopt() function parses the command line arguments.  Its arguments argc
and argv are the argument count and array as passed to the main() function
on program invocation.  The argument optstring is a list of available option
characters.  If such a character is followed by a colon (`:'), the option
takes an argument, which is placed in _optarg.  If such a character is
followed by two colons, the option takes an optional argument, which is
placed in _optarg.  If the option does not take an argument, _optarg is NULL.

The external variable _optind is the index of the next array element of argv
to be processed; it communicates from one call to the next which element to
process.

The getopt_long() function works like getopt() except that it also accepts
long options started by two dashes `--'.  If these take values, it is either
in the form

--arg=value

 or

--arg value

It takes the additional arguments longopts which is a pointer to the first
element of an array of type GETOPT_LONG_OPTION_T.  The last element of the
array has to be filled with NULL for the name field.

The longind pointer points to the index of the current long option relative
to longopts if it is non-NULL.

The getopt() function returns the option character if the option was found
successfully, `:' if there was a missing parameter for one of the options,
`?' for an unknown option character, and EOF for the end of the option list.

The getopt_long() function's return value is described in the header file.

The function getopt_long_only() is identical to getopt_long(), except that a
plus sign `+' can introduce long options as well as `--'.

The following describes how to deal with options that follow non-option
argv-elements.

If the caller did not specify anything, the default is REQUIRE_ORDER if the
environment variable POSIXLY_CORRECT is defined, PERMUTE otherwise.

REQUIRE_ORDER means don't recognize them as options; stop option processing
when the first non-option is seen.  This is what Unix does.  This mode of
operation is selected by either setting the environment variable
POSIXLY_CORRECT, or using `+' as the first character of the optstring
parameter.

PERMUTE is the default.  We permute the contents of ARGV as we scan, so that
eventually all the non-options are at the end.  This allows options to be
given in any order, even with programs that were not written to expect this.

RETURN_IN_ORDER is an option available to programs that were written to
expect options and other argv-elements in any order and that care about the
ordering of the two.  We describe each non-option argv-element as if it were
the argument of an option with character code 1.  Using `-' as the first
character of the optstring parameter selects this mode of operation.

The special argument `--' forces an end of option-scanning regardless of the
value of ordering.  In the case of RETURN_IN_ORDER, only `--' can cause
getopt() and friends to return EOF with _optind != argc.

COPYRIGHT NOTICE AND DISCLAIMER:

Copyright (C) 1997 Gregory Pietsch

This file and the accompanying getopt.h header file are hereby placed in the 
public domain without restrictions.  Just give the author credit, don't
claim you wrote it or prevent anyone else from using it.

Gregory Pietsch's current e-mail address:
gpietsch@comcast.net
****************************************************************************/

/* include files */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "getopt_long.h"

/* macros */

/* types */
typedef enum GETOPT_ORDERING_T
{
  PERMUTE,
  RETURN_IN_ORDER,
  REQUIRE_ORDER
} GETOPT_ORDERING_T;

/* globally-defined variables */
char *_optarg = NULL;
int _optind = 0;
int opterr = 1;
int _optopt = '?';

/* functions */

/* reverse_argv_elements:  reverses num elements starting at argv */
static void
reverse_argv_elements (char **argv, int num)
{
  int i;
  char *tmp;

  for (i = 0; i < (num >> 1); i++)
    {
      tmp = argv[i];
      argv[i] = argv[num - i - 1];
      argv[num - i - 1] = tmp;
    }
}

/* permute: swap two blocks of argv-elements given their lengths */
static void
permute (char **argv, int len1, int len2)
{
  reverse_argv_elements (argv, len1);
  reverse_argv_elements (argv, len1 + len2);
  reverse_argv_elements (argv, len2);
}

/* is_option: is this argv-element an option or the end of the option list? */
static int
is_option (char *argv_element, int only)
{
  return ((argv_element == NULL)
          || (argv_element[0] == '-') || (only && argv_element[0] == '+'));
}

/* getopt_internal:  the function that does all the dirty work */
static int
getopt_internal (int argc, char **argv, const char *shortopts,
                 const GETOPT_LONG_OPTION_T * longopts, int *longind, int only)
{
  GETOPT_ORDERING_T ordering = PERMUTE;
  static size_t optwhere = 0;
  size_t permute_from = 0;
  int num_nonopts = 0;
  int optindex = 0;
  size_t match_chars = 0;
  char *possible_arg = NULL;
  int longopt_match = -1;
  int has_arg = -1;
  char *cp = NULL;
  int arg_next = 0;

  /* first, deal with silly parameters and easy stuff */
  if (argc == 0 || argv == NULL || (shortopts == NULL && longopts == NULL)
    || _optind >= argc || argv[_optind] == NULL)
    return EOF;
  if (strcmp (argv[_optind], "--") == 0)
    {
      _optind++;
      return EOF;
    }
  /* if this is our first time through */
  if (_optind == 0)
    _optind = optwhere = 1;

  /* define ordering */
  if (shortopts != NULL && (*shortopts == '-' || *shortopts == '+'))
    {
      ordering = (*shortopts == '-') ? RETURN_IN_ORDER : REQUIRE_ORDER;
      shortopts++;
    }
  else
    ordering = /*(getenv ("POSIXLY_CORRECT") != NULL) ? REQUIRE_ORDER :*/ PERMUTE;

  /*
   * based on ordering, find our next option, if we're at the beginning of
   * one
   */
  if (optwhere == 1)
    {
      switch (ordering)
        {
        default:                /* shouldn't happen */
        case PERMUTE:
          permute_from = _optind;
          num_nonopts = 0;
          while (!is_option (argv[_optind], only))
            {
              _optind++;
              num_nonopts++;
            }
          if (argv[_optind] == NULL)
            {
              /* no more options */
              _optind = permute_from;
              return EOF;
            }
          else if (strcmp (argv[_optind], "--") == 0)
            {
              /* no more options, but have to get `--' out of the way */
              permute (argv + permute_from, num_nonopts, 1);
              _optind = permute_from + 1;
              return EOF;
            }
          break;
        case RETURN_IN_ORDER:
          if (!is_option (argv[_optind], only))
            {
              _optarg = argv[_optind++];
              return (_optopt = 1);
            }
          break;
        case REQUIRE_ORDER:
          if (!is_option (argv[_optind], only))
            return EOF;
          break;
        }
    }
  /* we've got an option, so parse it */

  /* first, is it a long option? */
  if (longopts != NULL
      && (memcmp (argv[_optind], "--", 2) == 0
          || (only && argv[_optind][0] == '+')) && optwhere == 1)
    {
      /* handle long options */
      if (memcmp (argv[_optind], "--", 2) == 0)
        optwhere = 2;
      longopt_match = -1;
      possible_arg = strchr (argv[_optind] + optwhere, '=');
      if (possible_arg == NULL)
        {
          /* no =, so next argv might be arg */
          match_chars = strlen (argv[_optind]);
          possible_arg = argv[_optind] + match_chars;
          match_chars = match_chars - optwhere;
        }
      else
        match_chars = (possible_arg - argv[_optind]) - optwhere;
      for (optindex = 0; longopts[optindex].name != NULL; optindex++)
        {
          if (memcmp (argv[_optind] + optwhere,
                      longopts[optindex].name, match_chars) == 0)
            {
              /* do we have an exact match? */
              if (match_chars == (unsigned) (strlen (longopts[optindex].name)))
                {
                  longopt_match = optindex;
                  break;
                }
              /* do any characters match? */
              else
                {
                  if (longopt_match < 0)
                    longopt_match = optindex;
                  else
                    {
                      /* we have ambiguous options */
                      if (opterr)
                        fprintf (stderr, "%s: option `%s' is ambiguous "
                                 "(could be `--%s' or `--%s')\n",
                                 argv[0],
                                 argv[_optind],
                                 longopts[longopt_match].name,
                                 longopts[optindex].name);
                      return (_optopt = '?');
                    }
                }
            }
        }
      if (longopt_match >= 0)
        has_arg = longopts[longopt_match].has_arg;
    }
  /* if we didn't find a long option, is it a short option? */
  if (longopt_match < 0 && shortopts != NULL)
    {
      cp = strchr (shortopts, argv[_optind][optwhere]);
      if (cp == NULL)
        {
          /* couldn't find option in shortopts */
          if (opterr)
            fprintf (stderr,
                     "%s: invalid option -- `-%c'\n",
                     argv[0], argv[_optind][optwhere]);
          optwhere++;
          if (argv[_optind][optwhere] == '\0')
            {
              _optind++;
              optwhere = 1;
            }
          return (_optopt = '?');
        }
      has_arg = ((cp[1] == ':')
                 ? ((cp[2] == ':') ? OPTIONAL_ARG : REQUIRED_ARG) : NO_ARG);
      possible_arg = argv[_optind] + optwhere + 1;
      _optopt = *cp;
    }
  /* get argument and reset optwhere */
  arg_next = 0;
  switch (has_arg)
    {
    case OPTIONAL_ARG:
      if (*possible_arg == '=')
        possible_arg++;
      _optarg = (*possible_arg != '\0') ? possible_arg : 0;
      optwhere = 1;
      break;
    case REQUIRED_ARG:
      if (*possible_arg == '=')
        possible_arg++;
      if (*possible_arg != '\0')
        {
          _optarg = possible_arg;
          optwhere = 1;
        }
      else if (_optind + 1 >= argc)
        {
          if (opterr)
            {
              fprintf (stderr, "%s: argument required for option `", argv[0]);
              if (longopt_match >= 0)
                fprintf (stderr, "--%s'\n", longopts[longopt_match].name);
              else
                fprintf (stderr, "-%c'\n", *cp);
            }
          _optind++;
          return (_optopt = ':');
        }
      else
        {
          _optarg = argv[_optind + 1];
          arg_next = 1;
          optwhere = 1;
        }
      break;
    default:                    /* shouldn't happen */
    case NO_ARG:
      if (longopt_match < 0)
        {
          optwhere++;
          if (argv[_optind][optwhere] == '\0')
            optwhere = 1;
        }
      else
        optwhere = 1;
      _optarg = NULL;
      break;
    }

  /* do we have to permute or otherwise modify _optind? */
  if (ordering == PERMUTE && optwhere == 1 && num_nonopts != 0)
    {
      permute (argv + permute_from, num_nonopts, 1 + arg_next);
      _optind = permute_from + 1 + arg_next;
    }
  else if (optwhere == 1)
    _optind = _optind + 1 + arg_next;

  /* finally return */
  if (longopt_match >= 0)
    {
      if (longind != NULL)
        *longind = longopt_match;
      if (longopts[longopt_match].flag != NULL)
        {
          *(longopts[longopt_match].flag) = longopts[longopt_match].val;
          return 0;
        }
      else
        return longopts[longopt_match].val;
    }
  else
    return _optopt;
}

#if 0
int
getopt (int argc, char **argv, char *optstring)
{
  return getopt_internal (argc, argv, optstring, NULL, NULL, 0);
}
#endif

int
getopt_long (int argc, char **argv, const char *shortopts,
             const GETOPT_LONG_OPTION_T * longopts, int *longind)
{
  return getopt_internal (argc, argv, shortopts, longopts, longind, 0);
}

int
getopt_long_only (int argc, char **argv, const char *shortopts,
                  const GETOPT_LONG_OPTION_T * longopts, int *longind)
{
  return getopt_internal (argc, argv, shortopts, longopts, longind, 1);
}

/* end of file GETOPT.C */
