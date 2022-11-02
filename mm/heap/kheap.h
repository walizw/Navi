/*
 * kheap.h - definitions for the navi heap.
 *
 * Copyright (C) 2022 walizw <yojan.bustamante@udea.edu.co>
 */

#ifndef __KHEAP_H
#define __KHEAP_H

#include "heap.h"

#include <drivers/vga/term.h>

void kheap_init ();
void *kmalloc (u32 size);
void *kzalloc (u32 size);
void kfree (void *ptr);

#endif
