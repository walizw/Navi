/*
 * disk.h - Basic ATA disk driver function definitions
 *
 * Copyright (C) 2022 walizw <yojan.bustamante@udea.edu.co>
 */

#ifndef __DISK_H
#define __DISK_H

#include <io/io.h>

#include <kernel.h>

int disk_read_sector (int lba, int total, void *buf);

#endif
