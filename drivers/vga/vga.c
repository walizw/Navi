/*
 * vga.c - Basic text mode functions.
 *
 * Copyright (C) 2022 walizw <yojan.bustamante@udea.edu.co>
 */

#include "vga.h"

u16 *vidmem = (u16 *)0xB8000;

/*
 * Makes a character merging its value and its desired colour.
 */
u16
vga_mkchar (char c, enum vga_col col)
{
  return (col << 8) | c;
}

/*
 * Places a single character (the one returned by the mkchar function) at an x
 * and y position.
 */
void
vga_putc (int x, int y, u16 c)
{
  vidmem[(y * VGA_WIDTH) + x] = c;
}
