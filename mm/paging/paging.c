/*
 * paging.c - Paging :p
 *
 * Copyright (C) 2022 walizw <yojan.bustamante@udea.edu.co>
 */

#include "paging.h"

/*
 * loads a paging directory (declared in assembly)
 */
void paging_load_directory (u32 *directory);

/*
 * current paging directory
 */
static u32 *cur_dir = 0;

/*
 * creates a new paging directory
 */
struct paging_4gb_chunk *
paging_new_4gb (u8 flags)
{
  u32 *dir = kzalloc (sizeof (u32) * PAGING_TOTAL_ENTRIES_PER_TABLE);
  int offset = 0;

  for (int i = 0; i < PAGING_TOTAL_ENTRIES_PER_TABLE; i++)
    {
      u32 *entry = kzalloc (sizeof (u32) * PAGING_TOTAL_ENTRIES_PER_TABLE);
      for (int j = 0; j < PAGING_TOTAL_ENTRIES_PER_TABLE; j++)
        {
          entry[j] = (offset + (j * PAGING_PAGE_SIZE)) | flags;
        }
      offset += (PAGING_TOTAL_ENTRIES_PER_TABLE * PAGING_PAGE_SIZE);
      dir[i] = (u32)entry | flags | PAGING_IS_WRITEABLE;
    }

  struct paging_4gb_chunk *chunk = kzalloc (sizeof (struct paging_4gb_chunk));
  chunk->dir_entry = dir;
  return chunk;
}

/*
 * switches between pages
 */
void
paging_switch (u32 *dir)
{
  paging_load_directory (dir);
  cur_dir = dir;
}

/*
 * returns the directory entry of a 4gb paging chunk
 */
u32 *
paging_4gb_chunk_get_directory (struct paging_4gb_chunk *chunk)
{
  return chunk->dir_entry;
}

/*
 * checks if an address is aligned
 */
_Bool
paging_is_aligned (void *addr)
{
  return ((u32)addr % PAGING_PAGE_SIZE) == 0;
}

/*
 * resolves a virtual address to its directory index and table index
 */
int
paging_get_indexes (void *virt_addr, u32 *dir_out, u32 *table_index_out)
{
  int res = 0;

  if (!paging_is_aligned (virt_addr))
    {
      res = -EINVARG;
      goto out;
    }

  *dir_out
      = ((u32)virt_addr / (PAGING_TOTAL_ENTRIES_PER_TABLE * PAGING_PAGE_SIZE));
  *table_index_out
      = ((u32)virt_addr % (PAGING_TOTAL_ENTRIES_PER_TABLE * PAGING_PAGE_SIZE)
         / PAGING_PAGE_SIZE);

out:
  return res;
}

/*
 * points an specified virtual address to an specified physical address
 */
int
paging_set (u32 *dir, void *virt, u32 val)
{
  if (!paging_is_aligned (virt))
    {
      return -EINVARG;
    }

  u32 dir_index = 0;
  u32 t_index = 0; // table index
  int res = paging_get_indexes (virt, &dir_index, &t_index);
  if (res < 0)
    return res;

  u32 entry = dir[dir_index];
  u32 *table = (u32 *)(entry & 0xfffff000);
  table[t_index] = val;

  return 0;
}
