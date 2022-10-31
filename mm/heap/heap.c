/*
 * heap.c - the heap implementation for the Navi kernel.
 *
 * Copyright (C) 2022 walizw <yojan.bustamante@udea.edu.co>
 */

#include "heap.h"

/*
 * validates that `ptr' and `end' are valid for the table passed
 */
static int
heap_validate_table (void *ptr, void *end, struct heap_table *table)
{
  int res = AOK;

  u32 table_size = (u32)(end - ptr);
  u32 total_blocks = table_size / NAVI_HEAP_BLOCK_SIZE;
  if (table->total != total_blocks)
    {
      // table miscalculated?
      res = -EINVARG;
      goto out;
    }

out:
  return res;
}

/*
 * validates the alignment of `ptr' and returns true or false, if it's aligned
 * or not
 */
static _Bool
heap_validate_alignment (void *ptr)
{
  return ((u32)ptr % NAVI_HEAP_BLOCK_SIZE) == 0;
}

/*
 * creates the heap, and returns 0 on success or a negative value (representing
 * an error code)
 */
int
heap_create (struct heap *heap, void *ptr, void *end, struct heap_table *table)
{
  int res = AOK;

  if (!heap_validate_alignment (ptr) || !heap_validate_alignment (end))
    {
      // it has to be alignment, bc we're using blocks
      res = -EINVARG;
      goto out;
    }

  memset (heap, 0, sizeof (struct heap));
  heap->saddr = ptr;
  heap->table = table;

  res = heap_validate_table (ptr, end, table);
  if (res < 0)
    {
      goto out;
    }

  // init all blocks to zero
  u32 table_size = sizeof (HEAP_BLOCK_TABLE_ENTRY) * table->total;
  memset (table->entries, NAVI_HEAP_BLOCK_TABLE_ENTRY_FREE, table_size);

out:
  return res;
}

/*
 * aligns a value based on block size, i.e. if block size is 4096 and `val' is
 * 50, this will return 4096, but if `val' is 4097 then we'll return 8192
 */
static u32
heap_align_value_to_upper (u32 val)
{
  if ((val % NAVI_HEAP_BLOCK_SIZE) == 0)
    {
      return val;
    }

  val = (val - (val % NAVI_HEAP_BLOCK_SIZE)); // aligns to lower
  val += NAVI_HEAP_BLOCK_SIZE;
  return val;
}

/*
 * gets the entry type of an entry
 */
static int
heap_get_entry_type (HEAP_BLOCK_TABLE_ENTRY entry)
{
  return entry & 0x0f;
}

/*
 * finds the first block with `total' number of contiguous next free blocks
 */
int
heap_get_start_block (struct heap *heap, u32 total)
{
  struct heap_table *table = heap->table;
  int bc = 0;  // current block we're on
  int bs = -1; // block start, first block we find

  for (u32 i = 0; i < table->total; i++)
    {
      if (heap_get_entry_type (table->entries[i])
          != NAVI_HEAP_BLOCK_TABLE_ENTRY_FREE)
        {
          // this entry is not free, reset state
          bc = 0;
          bs = -1;
          continue;
        }

      // if this is the first block
      if (bs == -1)
        {
          bs = i;
        }
      bc++;

      if (bc == total)
        {
          break;
        }
    }

  if (bs == -1)
    {
      return -ENOMEM;
    }

  return bs;
}

/*
 * gets the address of the block `block' in the heap
 */
void *
heap_block_to_addr (struct heap *heap, int block)
{
  return heap->saddr + (block * NAVI_HEAP_BLOCK_SIZE);
}

/*
 * marks `total' blocks as taken after `bs' so they are not taken into account
 * in future mallocs
 */
void
heap_mark_blocks_taken (struct heap *heap, int bs, int total)
{
  int end_block = (bs + total) - 1;

  HEAP_BLOCK_TABLE_ENTRY entry
      = NAVI_HEAP_BLOCK_TABLE_ENTRY_TAKEN | NAVI_HEAP_BLOCK_IS_FIRST;
  if (total > 1)
    {
      entry |= NAVI_HEAP_BLOCK_HAS_NEXT;
    }

  for (int i = bs; i <= end_block; i++)
    {
      heap->table->entries[i] = entry;
      entry = NAVI_HEAP_BLOCK_TABLE_ENTRY_TAKEN;
      if (i != end_block - 1)
        {
          entry |= NAVI_HEAP_BLOCK_HAS_NEXT;
        }
    }
}

/*
 * allocates memory in our heap (using number of blocks instead of bytes)
 */
void *
heap_malloc_blocks (struct heap *heap, u32 total)
{
  void *addr = 0;

  int start_block = heap_get_start_block (heap, total);
  if (start_block < 0)
    {
      goto out;
    }

  addr = heap_block_to_addr (heap, start_block);

  // mark the blocks as taken
  heap_mark_blocks_taken (heap, start_block, total);

out:
  return addr;
}

/*
 * allocates memory in our heap
 */
void *
heap_malloc (struct heap *heap, u32 size)
{
  u32 aligned_size = heap_align_value_to_upper (size);
  u32 total_blocks = aligned_size / NAVI_HEAP_BLOCK_SIZE;

  return heap_malloc_blocks (heap, total_blocks);
}

/*
 * converts `addr' to a block number of our heap table
 */
u32
heap_addr_to_block (struct heap *heap, void *addr)
{
  return ((u32)(addr - heap->saddr)) / NAVI_HEAP_BLOCK_SIZE;
}

/*
 * marks all the blocks from `bs' as free until found a block without
 * `HAS_NEXT'
 */
void
heap_mark_blocks_free (struct heap *heap, u32 bs)
{
  struct heap_table *table = heap->table;
  for (u32 i = bs; i < table->total; i++)
    {
      HEAP_BLOCK_TABLE_ENTRY entry = table->entries[i];
      table->entries[i] = NAVI_HEAP_BLOCK_TABLE_ENTRY_FREE;

      if (!(entry & NAVI_HEAP_BLOCK_HAS_NEXT))
        {
          break;
        }
    }
}

/*
 * frees memory in our heap
 */
void
heap_free (struct heap *heap, void *ptr)
{
  heap_mark_blocks_free (heap, heap_addr_to_block (heap, ptr));
}
