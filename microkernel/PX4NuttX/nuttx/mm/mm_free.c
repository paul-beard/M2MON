/****************************************************************************
 * mm/mm_free.c
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
#if defined(CONFIG_MEMGUARD_HEAP) || defined(CONFIG_MEMGUARD_PROFILE)
#include <nuttx/sched.h>
#endif
#include <nuttx/memguard.h>

/****************************************************************************
 * Pre-processor Definitions
 ****************************************************************************/

/****************************************************************************
 * Private Functions
 ****************************************************************************/

/****************************************************************************
 * Name: mm_free
 *
 * Description:
 *   Returns a chunk of memory to the list of free nodes,  merging with
 *   adjacent free chunks if possible.
 *
 ****************************************************************************/

#ifndef CONFIG_MM_MULTIHEAP
static inline
#endif
void mm_free(FAR struct mm_heap_s *heap, FAR void *mem)
{
  FAR struct mm_freenode_s *node;
  FAR struct mm_freenode_s *prev;
  FAR struct mm_freenode_s *next;

#ifdef CONFIG_MEMGUARD_HEAP
  seclldbg("Freeing %p: heap=%p\n", mem, heap);
#else
  mvdbg("Freeing %p\n", mem);
#endif

  /* Protect against attempts to free a NULL reference */

  if (!mem)
    {
      return;
    }

  /* We need to hold the MM semaphore while we muck with the
   * nodelist.
   */

  mm_takesemaphore(heap);

  /* Map the memory chunk into a free node */

  node = (FAR struct mm_freenode_s *)((char*)mem - SIZEOF_MM_ALLOCNODE);
  node->preceding &= ~MM_ALLOC_BIT;

  /* Check if the following node is free and, if so, merge it */

  next = (FAR struct mm_freenode_s *)((char*)node + node->size);
  if ((next->preceding & MM_ALLOC_BIT) == 0)
    {
      FAR struct mm_allocnode_s *andbeyond;

      /* Get the node following the next node (which will
       * become the new next node). We know that we can never
       * index past the tail chunk because it is always allocated.
       */

      andbeyond = (FAR struct mm_allocnode_s*)((char*)next + next->size);

      /* Remove the next node.  There must be a predecessor,
       * but there may not be a successor node.
       */

      DEBUGASSERT(next->blink);
      next->blink->flink = next->flink;
      if (next->flink)
        {
          next->flink->blink = next->blink;
        }

      /* Then merge the two chunks */

      node->size          += next->size;
      andbeyond->preceding =  node->size | (andbeyond->preceding & MM_ALLOC_BIT);
      next                 = (FAR struct mm_freenode_s *)andbeyond;
    }

  /* Check if the preceding node is also free and, if so, merge
   * it with this node
   */

  prev = (FAR struct mm_freenode_s *)((char*)node - node->preceding);
  if ((prev->preceding & MM_ALLOC_BIT) == 0)
    {
      /* Remove the node.  There must be a predecessor, but there may
       * not be a successor node.
       */

      DEBUGASSERT(prev->blink);
      prev->blink->flink = prev->flink;
      if (prev->flink)
        {
          prev->flink->blink = prev->blink;
        }

      /* Then merge the two chunks */

      prev->size     += node->size;
      next->preceding = prev->size | (next->preceding & MM_ALLOC_BIT);
      node            = prev;
    }

#ifdef CONFIG_MEMGUARD_PROFILE
  FAR struct tcb_s *rtcb = sched_self();
  if (!up_interrupt_context() && rtcb != &g_idletcb.cmn) {
    if (mem != rtcb->stack_alloc_ptr) {
      if (g_memguard_profile_list[rtcb->pid].heap_size > node->size)
        g_memguard_profile_list[rtcb->pid].heap_size -= node->size;
      else
        g_memguard_profile_list[rtcb->pid].heap_size = 0;
    }
  }
#endif

  /* Add the merged node to the nodelist */

  mm_addfreechunk(heap, node);
  mm_givesemaphore(heap);
}

/****************************************************************************
 * Public Functions
 ****************************************************************************/

/****************************************************************************
 * Name: free
 *
 * Description:
 *   Returns a chunk of memory to the list of free nodes,  merging with
 *   adjacent free chunks if possible.
 *
 ****************************************************************************/

#if !defined(CONFIG_NUTTX_KERNEL) || !defined(__KERNEL__)
void free(FAR void *mem)
{
#if defined(CONFIG_MEMGUARD_HEAP)
  FAR struct tcb_s *rtcb = sched_self();
  if (up_interrupt_context() || rtcb == &g_idletcb.cmn)
    mm_free(&g_mmheap, mem);
  else
    mm_free(&rtcb->mmheap, mem);
#else
  mm_free(&g_mmheap, mem);
#endif
}
#endif
