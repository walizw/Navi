/*
 * streamer.c - A streamer for the ATA driver so we can read more - or less -
 * bytes than those defined by the sector size.
 *
 * Copyright (C) 2022 walizw <yojan.bustamante@udea.edu.co>
 */
#include "streamer.h"

/*
 * creates a new disk streamer on `disk_id'.
 */
struct disk_streamer *
disk_streamer_new (int disk_id)
{
  struct disk *disk = disk_get (disk_id);
  if (!disk)
    return 0x00;

  struct disk_streamer *streamer = kzalloc (sizeof (struct disk_streamer));
  streamer->pos = 0;
  streamer->disk = disk;
  return streamer;
}

/*
 * seeks `streamer' to `pos'.
 */
int
disk_streamer_seek (struct disk_streamer *streamer, int pos)
{
  streamer->pos = pos;
  return 0;
}

/*
 * reads `total' from `streamer' into `out'.
 */
int
disk_streamer_read (struct disk_streamer *streamer, void *out, int total)
{
  int sector = streamer->pos / NAVI_SECTOR_SIZE;
  int offset = streamer->pos % NAVI_SECTOR_SIZE;
  char buf[NAVI_SECTOR_SIZE];

  int res = disk_read_block (streamer->disk, sector, 1, buf);
  if (res < 0)
    goto out;

  int total_to_read = total > NAVI_SECTOR_SIZE ? NAVI_SECTOR_SIZE : total;
  for (int i = 0; i < total_to_read; i++)
    {
      *(char *)out++ = buf[offset + 1];
    }

  // adjust the stream
  streamer->pos += total_to_read;
  if (total > NAVI_SECTOR_SIZE)
    {
      res = disk_streamer_read (streamer, out, total - NAVI_SECTOR_SIZE);
    }

out:
  return res;
}

/*
 * closes a disk streamer.
 */
void
disk_streamer_close (struct disk_streamer *streamer)
{
  kfree (streamer);
  streamer = 0x00;
}
