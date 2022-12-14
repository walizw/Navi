/*
 * kheap.c - the heap used in the navi kernel, think of `heap' as the container
 * for the heap functionality, and `kheap' as the actual implementation, as
 * here is defined the heap that the kernel will be using.
 *
 * Copyright (C) 2022 walizw <yojan.bustamante@udea.edu.co>
 */

#include "kheap.h"

struct heap kheap;
struct heap_table kheap_table;

/*
 * initialises the kernel heap
 */
void
kheap_init ()
{
  int total_table_entries = NAVI_HEAP_SIZE_BYTES / NAVI_HEAP_BLOCK_SIZE;
  kheap_table.entries = (HEAP_BLOCK_TABLE_ENTRY *)(NAVI_HEAP_TABLE_ADDR);
  kheap_table.total = total_table_entries;

  void *end
      = (void *)(NAVI_HEAP_ADDR + NAVI_HEAP_SIZE_BYTES); // end of our table
  int res = heap_create (&kheap, (void *)(NAVI_HEAP_ADDR), end, &kheap_table);
  if (res < 0)
    {
      // TODO: Panic
      term_print ("failed to create heap\n");
    }
}

/*
 * allocates memory in the kernel heap
 */
void *
kmalloc (u32 size)
{
  return heap_malloc (&kheap, size);
}

/*
 * allocates memory and zeroes it
 */
void *
kzalloc (u32 size)
{
  void *ptr = kmalloc (size);
  if (!ptr)
    {
      return 0x00;
    }

  memset (ptr, 0x00, size);
  return ptr;
}

/*
 * frees memory in the kernel heap
 */
void
kfree (void *ptr)
{
  return heap_free (&kheap, ptr);
}
