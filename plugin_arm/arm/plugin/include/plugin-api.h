/* plugin-api.h -- External linker plugin API.  */

/* Copyright 2009, 2010 Free Software Foundation, Inc.
   Written by Cary Coutant <ccoutant@google.com>.

   This file is part of binutils.

   This program is free software; you can redistribute it and/or modify
   it under the terms of the GNU General Public License as published by
   the Free Software Foundation; either version 3 of the License, or
   (at your option) any later version.

   This program is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
   GNU General Public License for more details.

   You should have received a copy of the GNU General Public License
   along with this program; if not, write to the Free Software
   Foundation, Inc., 51 Franklin Street - Fifth Floor, Boston,
   MA 02110-1301, USA.  */

/* This file defines the interface for writing a linker plugin, which is
   described at < http://gcc.gnu.org/wiki/whopr/driver >.  */

#ifndef PLUGIN_API_H
#define PLUGIN_API_H

#ifdef HAVE_STDINT_H
#include <stdint.h>
#elif defined(HAVE_INTTYPES_H)
#include <inttypes.h>
#endif
#include <sys/types.h>
#if !defined(HAVE_STDINT_H) && !defined(HAVE_INTTYPES_H) && \
    !defined(UINT64_MAX) && !defined(uint64_t)
#error can not find uint64_t type
#endif

#ifdef __cplusplus
extern "C"
{
#endif

/* Status code returned by most API routines.  */

enum ld_plugin_status
{
  LDPS_OK = 0,
  LDPS_NO_SYMS,         /* Attempt to get symbols that haven't been added. */
  LDPS_BAD_HANDLE,      /* No claimed object associated with given handle. */
  LDPS_ERR
  /* Additional Error codes TBD.  */
};

/* The version of the API specification.  */

enum ld_plugin_api_version
{
  LD_PLUGIN_API_VERSION = 1
};

/* The type of output file being generated by the linker.  */

enum ld_plugin_output_file_type
{
  LDPO_REL,
  LDPO_EXEC,
  LDPO_DYN,
  LDPO_PIE
};

/* An input file managed by the plugin library.  */

struct ld_plugin_input_file
{
  const char *name;
  int fd;
  off_t offset;
  off_t filesize;
  void *handle;
};

/* A symbol belonging to an input file managed by the plugin library.  */

struct ld_plugin_symbol
{
  char *name;
  char *version;
  int def;
  int visibility;
  uint64_t size;
  char *comdat_key;
  int resolution;
};

/* An object's section.  */

struct ld_plugin_section
{
  const void* handle;
  unsigned int shndx;
};

/* Whether the symbol is a definition, reference, or common, weak or not.  */

enum ld_plugin_symbol_kind
{
  LDPK_DEF,
  LDPK_WEAKDEF,
  LDPK_UNDEF,
  LDPK_WEAKUNDEF,
  LDPK_COMMON
};

/* The visibility of the symbol.  */

enum ld_plugin_symbol_visibility
{
  LDPV_DEFAULT,
  LDPV_PROTECTED,
  LDPV_INTERNAL,
  LDPV_HIDDEN
};

/* How a symbol is resolved.  */

enum ld_plugin_symbol_resolution
{
  LDPR_UNKNOWN = 0,

  /* Symbol is still undefined at this point.  */
  LDPR_UNDEF,

  /* This is the prevailing definition of the symbol, with references from
     regular object code.  */
  LDPR_PREVAILING_DEF,

  /* This is the prevailing definition of the symbol, with no
     references from regular objects.  It is only referenced from IR
     code.  */
  LDPR_PREVAILING_DEF_IRONLY,

  /* This definition was pre-empted by a definition in a regular
     object file.  */
  LDPR_PREEMPTED_REG,

  /* This definition was pre-empted by a definition in another IR file.  */
  LDPR_PREEMPTED_IR,

  /* This symbol was resolved by a definition in another IR file.  */
  LDPR_RESOLVED_IR,

  /* This symbol was resolved by a definition in a regular object
     linked into the main executable.  */
  LDPR_RESOLVED_EXEC,

  /* This symbol was resolved by a definition in a shared object.  */
  LDPR_RESOLVED_DYN,

  /* This is the prevailing definition of the symbol, with no
     references from regular objects.  It is only referenced from IR
     code, but the symbol is exported and may be referenced from
     a dynamic object (not seen at link time).  */
  LDPR_PREVAILING_DEF_IRONLY_EXP
};

/* The plugin library's "claim file" handler.  */

typedef
enum ld_plugin_status
(*ld_plugin_claim_file_handler) (
  const struct ld_plugin_input_file *file, int *claimed);

/* The plugin library's "all symbols read" handler.  */

typedef
enum ld_plugin_status
(*ld_plugin_all_symbols_read_handler) (void);

/* The plugin library's cleanup handler.  */

typedef
enum ld_plugin_status
(*ld_plugin_cleanup_handler) (void);

/* The linker's interface for registering the "claim file" handler.  */

typedef
enum ld_plugin_status
(*ld_plugin_register_claim_file) (ld_plugin_claim_file_handler handler);

/* The linker's interface for registering the "all symbols read" handler.  */

typedef
enum ld_plugin_status
(*ld_plugin_register_all_symbols_read) (
  ld_plugin_all_symbols_read_handler handler);

/* The linker's interface for registering the cleanup handler.  */

typedef
enum ld_plugin_status
(*ld_plugin_register_cleanup) (ld_plugin_cleanup_handler handler);

/* The linker's interface for adding symbols from a claimed input file.  */

typedef
enum ld_plugin_status
(*ld_plugin_add_symbols) (void *handle, int nsyms,
                          const struct ld_plugin_symbol *syms);

/* The linker's interface for getting the input file information with
   an open (possibly re-opened) file descriptor.  */

typedef
enum ld_plugin_status
(*ld_plugin_get_input_file) (const void *handle,
                             struct ld_plugin_input_file *file);

typedef
enum ld_plugin_status
(*ld_plugin_get_view) (const void *handle, const void **viewp);

/* The linker's interface for releasing the input file.  */

typedef
enum ld_plugin_status
(*ld_plugin_release_input_file) (const void *handle);

/* The linker's interface for retrieving symbol resolution information.  */

typedef
enum ld_plugin_status
(*ld_plugin_get_symbols) (const void *handle, int nsyms,
                          struct ld_plugin_symbol *syms);

/* The linker's interface for adding a compiled input file.  */

typedef
enum ld_plugin_status
(*ld_plugin_add_input_file) (const char *pathname);

/* The linker's interface for adding a library that should be searched.  */

typedef
enum ld_plugin_status
(*ld_plugin_add_input_library) (const char *libname);

/* The linker's interface for adding a library path that should be searched.  */

typedef
enum ld_plugin_status
(*ld_plugin_set_extra_library_path) (const char *path);

/* The linker's interface for issuing a warning or error message.  */

typedef
enum ld_plugin_status
(*ld_plugin_message) (int level, const char *format, ...);

/* The linker's interface for retrieving the number of sections in an object.
   The handle is obtained in the claim_file handler.  This interface should
   only be invoked in the claim_file handler.   This function sets *COUNT to
   the number of sections in the object.  */

typedef
enum ld_plugin_status
(*ld_plugin_get_input_section_count) (const void* handle, unsigned int *count);

/* The linker's interface for retrieving the section type of a specific
   section in an object.  This interface should only be invoked in the
   claim_file handler.  This function sets *TYPE to an ELF SHT_xxx value.  */

typedef
enum ld_plugin_status
(*ld_plugin_get_input_section_type) (const struct ld_plugin_section section,
                                     unsigned int *type);

/* The linker's interface for retrieving the name of a specific section in
   an object. This interface should only be invoked in the claim_file handler.
   This function sets *SECTION_NAME_PTR to a null-terminated buffer allocated
   by malloc.  The plugin must free *SECTION_NAME_PTR.  */

typedef
enum ld_plugin_status
(*ld_plugin_get_input_section_name) (const struct ld_plugin_section section,
                                     char **section_name_ptr);

/* The linker's interface for retrieving the contents of a specific section
   in an object.  This interface should only be invoked in the claim_file
   handler.  This function sets *SECTION_CONTENTS to point to a buffer that is
   valid until clam_file handler returns.  It sets *LEN to the size of the
   buffer.  */

typedef
enum ld_plugin_status
(*ld_plugin_get_input_section_contents) (const struct ld_plugin_section section,
                                         const unsigned char **section_contents,
                                         size_t* len);

/* The linker's interface for specifying the desired order of sections.
   The sections should be specifed using the array SECTION_LIST in the
   order in which they should appear in the final layout.  NUM_SECTIONS
   specifies the number of entries in each array.  This should be invoked
   in the all_symbols_read handler.  */

typedef
enum ld_plugin_status
(*ld_plugin_update_section_order) (const struct ld_plugin_section *section_list,
				   unsigned int num_sections);

/* The linker's interface for specifying that reordering of sections is
   desired so that the linker can prepare for it.  This should be invoked
   before update_section_order, preferably in the claim_file handler.  */

typedef
enum ld_plugin_status
(*ld_plugin_allow_section_ordering) (void);

/* The linker's interface for specifying that a subset of sections is
   to be mapped to a unique segment.  If the plugin wants to call
   unique_segment_for_sections, it must call this function from a
   claim_file_handler or when it is first loaded.  */

typedef
enum ld_plugin_status
(*ld_plugin_allow_unique_segment_for_sections) (void);

/* The linker's interface for specifying that a specific set of sections
   must be mapped to a unique segment.  ELF segments do not have names
   and the NAME is used as the name of the newly created output section
   that is then placed in the unique PT_LOAD segment.  FLAGS is used to
   specify if any additional segment flags need to be set.  For instance,
   a specific segment flag can be set to identify this segment.  Unsetting
   segment flags that would be set by default is not possible.  The
   parameter SEGMENT_ALIGNMENT when non-zero will override the default.  */

typedef
enum ld_plugin_status
(*ld_plugin_unique_segment_for_sections) (
    const char* segment_name,
    uint64_t segment_flags,
    uint64_t segment_alignment,
    const struct ld_plugin_section * section_list,
    unsigned int num_sections);

enum ld_plugin_level
{
  LDPL_INFO,
  LDPL_WARNING,
  LDPL_ERROR,
  LDPL_FATAL
};

/* Values for the tv_tag field of the transfer vector.  */

enum ld_plugin_tag
{
  LDPT_NULL = 0,
  LDPT_API_VERSION = 1,
  LDPT_GOLD_VERSION = 2,
  LDPT_LINKER_OUTPUT = 3,
  LDPT_OPTION = 4,
  LDPT_REGISTER_CLAIM_FILE_HOOK = 5,
  LDPT_REGISTER_ALL_SYMBOLS_READ_HOOK = 6,
  LDPT_REGISTER_CLEANUP_HOOK = 7,
  LDPT_ADD_SYMBOLS = 8,
  LDPT_GET_SYMBOLS = 9,
  LDPT_ADD_INPUT_FILE = 10,
  LDPT_MESSAGE = 11,
  LDPT_GET_INPUT_FILE = 12,
  LDPT_RELEASE_INPUT_FILE = 13,
  LDPT_ADD_INPUT_LIBRARY = 14,
  LDPT_OUTPUT_NAME = 15,
  LDPT_SET_EXTRA_LIBRARY_PATH = 16,
  LDPT_GNU_LD_VERSION = 17,
  LDPT_GET_VIEW = 18,
  LDPT_GET_INPUT_SECTION_COUNT = 19,
  LDPT_GET_INPUT_SECTION_TYPE = 20,
  LDPT_GET_INPUT_SECTION_NAME = 21,
  LDPT_GET_INPUT_SECTION_CONTENTS = 22,
  LDPT_UPDATE_SECTION_ORDER = 23,
  LDPT_ALLOW_SECTION_ORDERING = 24,
  LDPT_GET_SYMBOLS_V2 = 25,
  LDPT_ALLOW_UNIQUE_SEGMENT_FOR_SECTIONS = 26,
  LDPT_UNIQUE_SEGMENT_FOR_SECTIONS = 27
};

/* The plugin transfer vector.  */

struct ld_plugin_tv
{
  enum ld_plugin_tag tv_tag;
  union
  {
    int tv_val;
    const char *tv_string;
    ld_plugin_register_claim_file tv_register_claim_file;
    ld_plugin_register_all_symbols_read tv_register_all_symbols_read;
    ld_plugin_register_cleanup tv_register_cleanup;
    ld_plugin_add_symbols tv_add_symbols;
    ld_plugin_get_symbols tv_get_symbols;
    ld_plugin_add_input_file tv_add_input_file;
    ld_plugin_message tv_message;
    ld_plugin_get_input_file tv_get_input_file;
    ld_plugin_get_view tv_get_view;
    ld_plugin_release_input_file tv_release_input_file;
    ld_plugin_add_input_library tv_add_input_library;
    ld_plugin_set_extra_library_path tv_set_extra_library_path;
    ld_plugin_get_input_section_count tv_get_input_section_count;
    ld_plugin_get_input_section_type tv_get_input_section_type;
    ld_plugin_get_input_section_name tv_get_input_section_name;
    ld_plugin_get_input_section_contents tv_get_input_section_contents;
    ld_plugin_update_section_order tv_update_section_order;
    ld_plugin_allow_section_ordering tv_allow_section_ordering;
    ld_plugin_allow_unique_segment_for_sections tv_allow_unique_segment_for_sections; 
    ld_plugin_unique_segment_for_sections tv_unique_segment_for_sections;
  } tv_u;
};

/* The plugin library's "onload" entry point.  */

typedef
enum ld_plugin_status
(*ld_plugin_onload) (struct ld_plugin_tv *tv);

#ifdef __cplusplus
}
#endif

#endif /* !defined(PLUGIN_API_H) */
