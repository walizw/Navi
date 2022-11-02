/*
 * paging.h - Definitions for the navi's paging implementation.
 *
 * Copyright (C) 2022 walizw <yojan.bustamante@udea.edu.co>
 */

#ifndef __PAGING_H
#define __PAGING_H

#include <kernel.h>
#include <mm/heap/kheap.h>

#define PAGING_CACHE_DISABLED 0b00010000
#define PAGING_WRITE_THROUGH 0b00001000
#define PAGING_ACCESS_FROM_ALL 0b00000100 // user/supervisor
#define PAGING_IS_WRITEABLE 0b00000010
#define PAGING_IS_PRESENT 0b00000001

#define PAGING_TOTAL_ENTRIES_PER_TABLE 1024
#define PAGING_PAGE_SIZE 4096

/*
 * paging directory that maps an entire 4gb space
 */
struct paging_4gb_chunk
{
  u32 *dir_entry;
};

struct paging_4gb_chunk *paging_new_4gb (u8 flags);
void paging_switch (u32 *dir);
u32 *paging_4gb_chunk_get_directory (struct paging_4gb_chunk *chunk);

_Bool paging_is_aligned (void *addr);
int paging_set (u32 *dir, void *virt, u32 val);

/*
 * enables paging (should not be called until a 4gb chunk is created and
 * switched to it)
 */
void paging_enable ();

#endif
