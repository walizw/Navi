/*
 * io.c - Functions for outputting and getting info from the CPU bus.
 *
 * Copyright (C) 2022 walizw <yojan.bustamante@udea.edu.co>
 */

#ifndef __IO_H
#define __IO_H

#include <kernel.h>

u8 insb (u16 port);
u16 insw (u8 port);

void outb (u16 port, u8 val);
void outw (u16 port, u16 val);

#endif
