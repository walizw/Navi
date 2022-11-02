/*
 * heap.h - definitions for the heap implementation of the navi kernel.
 *
 * Copyright (C) 2022 walizw <yojan.bustamante@udea.edu.co>
 */

#ifndef __HEAP_H
#define __HEAP_H

#include <config.h>
#include <kernel.h>
#include <status.h>

#include <mm/mm.h>

#define NAVI_HEAP_BLOCK_TABLE_ENTRY_TAKEN 0x01
#define NAVI_HEAP_BLOCK_TABLE_ENTRY_FREE 0x00

#define NAVI_HEAP_BLOCK_HAS_NEXT 0b10000000
#define NAVI_HEAP_BLOCK_IS_FIRST 0b01000000

typedef unsigned char HEAP_BLOCK_TABLE_ENTRY;

/*
 * the heap table
 */
struct heap_table
{
  HEAP_BLOCK_TABLE_ENTRY *entries;
  u32 total; // total entries
};

/*
 * heap structure containing the table and its starting address
 */
struct heap
{
  struct heap_table *table;
  void *saddr; // start address
};

int heap_create (struct heap *heap, void *ptr, void *end,
                 struct heap_table *table);

void *heap_malloc (struct heap *heap, u32 size);
void heap_free (struct heap *heap, void *ptr);

#endif
