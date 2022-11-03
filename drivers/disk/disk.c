/*
 * disk.c - Basic ATA disk driver implementation
 *
 * Copyright (C) 2022 walizw <yojan.bustamante@udea.edu.co>
 */

#include "disk.h"

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
