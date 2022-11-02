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
