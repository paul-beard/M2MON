/****************************************************************************
 * mm/mm_mallinfo.c
 *
 *   Copyright (C) 2007, 2009, 2013 Gregory Nutt. All rights reserved.
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
#include <assert.h>
#include <debug.h>

#include <nuttx/mm.h>
#ifdef CONFIG_MEMGUARD_HEAP
#include <nuttx/sched.h>
#endif

/****************************************************************************
 * Pre-processor Definitions
 ****************************************************************************/

/****************************************************************************
 * Private Data
 ****************************************************************************/

/****************************************************************************
 * Private Functions
 ****************************************************************************/

/****************************************************************************
 * Name: mm_mallinfo
 *
 * Description:
 *   mallinfo returns a copy of updated current heap information.
 *
 ****************************************************************************/

#ifndef CONFIG_MM_MULTIHEAP
static inline
#endif
int mm_mallinfo(FAR struct mm_heap_s *heap, FAR struct mallinfo *info)
{
  struct mm_allocnode_s *node;
  size_t mxordblk = 0; 
  int    ordblks  = 0;  /* Number of non-inuse chunks */
  size_t uordblks = 0;  /* Total allocated space */
  size_t fordblks = 0;  /* Total non-inuse space */
#if CONFIG_MM_REGIONS > 1
  int region;
#else
# define region 0
#endif

  DEBUGASSERT(info);

  /* Visit each region */

#if CONFIG_MM_REGIONS > 1
  for (region = 0; region < heap->mm_nregions; region++)
#endif
    {
      /* Visit each node in the region
       * Retake the semaphore for each region to reduce latencies
       */
      
      mm_takesemaphore(heap);

      for (node = heap->mm_heapstart[region];
           node < heap->mm_heapend[region];
           node = (struct mm_allocnode_s *)((char*)node + node->size))
        {
          mvdbg("region=%d node=%p size=%p preceding=%p\n", region, node, node->size, node->preceding);
          if (node->preceding & MM_ALLOC_BIT)
            {
              uordblks += node->size;
            }
          else
            {
              ordblks++;
              fordblks += node->size;
              if (node->size > mxordblk)
                {
                  mxordblk = node->size;
                }
            }
        }

      mm_givesemaphore(heap);
        
      mvdbg("region=%d node=%p heapend=%p\n", region, node, heap->mm_heapend[region]);
      DEBUGASSERT(node == heap->mm_heapend[region]);
      uordblks += SIZEOF_MM_ALLOCNODE; /* account for the tail node */
    }
#undef region

  DEBUGASSERT(uordblks + fordblks == heap->mm_heapsize);

  info->arena    = heap->mm_heapsize;
  info->ordblks  = ordblks;
  info->mxordblk = mxordblk;
  info->uordblks = uordblks;
  info->fordblks = fordblks;
  return OK;
}

/****************************************************************************
 * Public Functions
 ****************************************************************************/

/****************************************************************************
 * Name: kmallinfo and mallinfo
 *
 * Description:
 *   mallinfo returns a copy of updated current heap information for either
 *   the user heap (mallinfo) or the kernel heap (kmallinfo).
 *
 ****************************************************************************/

#if !defined(CONFIG_NUTTX_KERNEL) || !defined(__KERNEL__)
#  ifdef CONFIG_CAN_PASS_STRUCTS

struct mallinfo mallinfo(void)
{
  struct mallinfo info;

#ifdef CONFIG_MEMGUARD_HEAP
  FAR struct tcb_s *rtcb = sched_self();
  if (up_interrupt_context() || rtcb == &g_idletcb.cmn)
    mm_mallinfo(&g_mmheap, &info);
  else
    mm_mallinfo(&rtcb->mmheap, &info);
#else
  mm_mallinfo(&g_mmheap, &info);
#endif
  return info;
}

#  else

int mallinfo(struct mallinfo *info)
{
#ifdef CONFIG_MEMGUARD_HEAP
  FAR struct tcb_s *rtcb = sched_self();
  if (up_interrupt_context() || rtcb == &g_idletcb.cmn)
    return mm_mallinfo(&g_mmheap, info);
  return mm_mallinfo(&rtcb->mmheap, info);
#else
  return mm_mallinfo(&g_mmheap, info);
#endif
}

#endif
#endif /* !CONFIG_NUTTX_KERNEL || !__KERNEL__ */
