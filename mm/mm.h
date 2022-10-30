/*
 * mm.h - Definitions for generic and simple memory management functions.
 *
 * Copyright (C) 2022 walizw <yojan.bustamante@udea.edu.co>
 */

#ifndef __MM_H
#define __MM_H

#include <kernel.h>

void *memset (void *ptr, int c, u32 size);

#endif
