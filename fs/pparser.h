/*
 * pparser.h - A simple path parser used to manage filesystems in the navi
 * operating system.
 *
 * Copyright (C) 2022 walizw <yojan.bustamante@udea.edu.co>
 */

#ifndef __PPARSER_H
#define __PPARSER_H

#include <config.h>
#include <status.h>

#include <mm/heap/kheap.h>
#include <mm/mm.h>

#include <string/string.h>

struct path_part;

struct path_root
{
  int drive_no;
  struct path_part *first;
};

struct path_part
{
  const char *part;
  struct path_part *next;
};

struct path_root *pparser_parse (const char *path, const char *current);
void pparser_free (struct path_root *root);

#endif
