/*
 * streamer.h - A streamer for the ATA driver.
 *
 * Copyright (C) 2022 walizw <yojan.bustamante@udea.edu.co>
 */
#ifndef __DISK_STREAMER_H
#define __DISK_STREAMER_H

#include "disk.h"

#include <config.h>

#include <mm/heap/kheap.h>

struct disk_streamer
{
  int pos;
  struct disk *disk;
};

struct disk_streamer *disk_streamer_new (int disk_id);
int disk_streamer_seek (struct disk_streamer *stream, int pos);
int disk_streamer_read (struct disk_streamer *stream, void *out, int total);
void disk_streamer_close (struct disk_streamer *streamer);

#endif
