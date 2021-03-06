/****************************************************************************
 * mm/mm_calloc.c
 *
 *   Copyright (C) 2007, 2009 Gregory Nutt. All rights reserved.
 *   Author: Gregory Nutt <gnutt@nuttx.org>
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions
 * are met:
 *
 * 1. Redistributions of source code must retain the above copyright
 *    notice, this list of conditions and the following disclaimer.
 * 2. Redistributions in binary form must reproduce the above copyright
 *    notice, this list of conditions and the following disclaimer in
 *    the documentation and/or other materials provided with the
 *    distribution.
 * 3. Neither the name NuttX nor the names of its contributors may be
 *    used to endorse or promote products derived from this software
 *    without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
 * "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT
 * LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS
 * FOR A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE
 * COPYRIGHT OWNER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT,
 * INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING,
 * BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS
 * OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED
 * AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT
 * LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN
 * ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE
 * POSSIBILITY OF SUCH DAMAGE.
 *
 ****************************************************************************/

/****************************************************************************
 * Included Files
 ****************************************************************************/

#include <nuttx/config.h>

#include <stdlib.h>

#include <nuttx/mm.h>
#ifdef CONFIG_MEMGUARD_HEAP
#include <nuttx/sched.h>
#endif

/****************************************************************************
 * Pre-processor Definitions
 ****************************************************************************/

/****************************************************************************
 * Global Functions
 ****************************************************************************/

/****************************************************************************
 * Name: mm_calloc
 *
 * Descripton:
 *   calloc calculates the size of the allocation and calls zalloc
 *
 ****************************************************************************/

#ifdef CONFIG_MM_MULTIHEAP
FAR void *mm_calloc(FAR struct mm_heap_s *heap, size_t n, size_t elem_size)
{
  FAR void *ret = NULL;

  if (n > 0 && elem_size > 0)
    {
      ret = mm_zalloc(heap, n * elem_size);
    }

  return ret;
}
#endif

/****************************************************************************
 * Name: calloc
 *
 * Descripton:
 *   calloc calculates the size of the allocation and calls zalloc
 *
 ****************************************************************************/

#if !defined(CONFIG_NUTTX_KERNEL) || !defined(__KERNEL__)
FAR void *calloc(size_t n, size_t elem_size)
{
#ifdef CONFIG_MM_MULTIHEAP
#ifdef CONFIG_MEMGUARD_HEAP
  FAR struct tcb_s *rtcb = sched_self();
  if (up_interrupt_context() || rtcb == &g_idletcb.cmn)
    return mm_calloc(&g_mmheap, n, elem_size);
  return mm_calloc(&rtcb->mmheap, n, elem_size);
#else
  return mm_calloc(&g_mmheap, n, elem_size);
#endif
#else
  FAR void *ret = NULL;

  if (n > 0 && elem_size > 0)
    {
      ret = zalloc(n * elem_size);
    }

  return ret;
#endif
}
#endif
