/*
 * io.c - Functions for outputting and getting info from the CPU bus.
 *
 * Copyright (C) 2022 walizw <yojan.bustamante@udea.edu.co>
 */

#ifndef __IO_H
#define __IO_H

#include <kernel.h>

/*
 * Gets a byte from `port' in processor bus.
 */
u8 insb (u16 port);

/*
 * Gets a word from `port' in the processor bus.
 */
u16 insw (u16 port);

/*
 * Outputs `val' byte to the `port' in processor bus.
 */
void outb (u16 port, u8 val);

/*
 * Outputs `val' word to the `port' in processor bus.
 */
void outw (u16 port, u16 val);

#endif
