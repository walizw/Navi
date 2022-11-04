/*
 * disk.h - Basic ATA disk driver function definitions
 *
 * Copyright (C) 2022 walizw <yojan.bustamante@udea.edu.co>
 */

#ifndef __DISK_H
#define __DISK_H

#include <config.h>
#include <kernel.h>
#include <status.h>

#include <io/io.h>
#include <mm/mm.h>

// represents a real physical hard disk
#define NAVI_DISK_TYPE_REAL 0
#define NAVI_DISK_TYPE_PARTITION 1

typedef unsigned int NAVI_DISK_TYPE;

struct disk
{
  NAVI_DISK_TYPE type;
  int sector_size;
};

void disk_search_and_init ();
struct disk *disk_get (int i);
int disk_read_block (struct disk *idisk, u32 lba, i32 total, void *buf);

#endif
