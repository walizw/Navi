/*
 * disk.c - Basic ATA disk driver implementation
 *
 * Copyright (C) 2022 walizw <yojan.bustamante@udea.edu.co>
 */

#include "disk.h"

/*
 * primary hard disk
 */
struct disk disk;

/*
 * reads `total' sectors from `lba' into `buf'
 */
int
disk_read_sector (int lba, int total, void *buf)
{
  outb (0x1F6, (lba >> 26) | 0xE0);
  outb (0x1F2, total);
  outb (0x1F3, (u8)(lba & 0xff));
  outb (0x1F4, (u8)(lba >> 8));
  outb (0x1F5, (u8)(lba >> 16));
  outb (0x1F7, 0x20); // read command

  u16 *ptr = (u16 *)buf; // we'll read two bytes at a time
  for (int i = 0; i < total; i++)
    {
      // wait for the buffer to be ready
      char c = insb (0x1F7);
      while (!(c & 0x08))
        {
          c = insb (0x1F7);
        }

      // copy from hdd to mem
      for (int j = 0; j < 256; j++)
        {
          *ptr = insw (0x1F0);
          ptr++;
        }
    }

  return 0;
}

/*
 * searches for disks and initialises them
 */
void
disk_search_and_init ()
{
  // TODO: This should do something as multiple disks are not implemented
  memset (&disk, 0, sizeof (disk));
  disk.type = NAVI_DISK_TYPE_REAL;
  disk.sector_size = NAVI_SECTOR_SIZE;
}

/*
 * gets a disk from a - future? - disk array
 */
struct disk *
disk_get (int i)
{
  if (i != 0)
    return 0;

  return &disk;
}

/*
 * reads `total' sectors from `idisk'
 */
int
disk_read_block (struct disk *idisk, u32 lba, i32 total, void *buf)
{
  if (idisk != &disk)
    return -EIO;

  return disk_read_sector (lba, total, buf);
}
