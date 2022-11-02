/*
 * vga.h - Definitions of basic VGA functions and the colours available in text
 * mode.
 *
 * Copyright (C) 2022 walizw <yojan.bustamante@udea.edu.co>
 */

#ifndef __VGA_H
#define __VGA_H

#define VGA_WIDTH 80
#define VGA_HEIGHT 20

#include <kernel.h>

/*
 * the available vga colours
 */
enum vga_col
{
  VGA_BLACK,
  VGA_BLUE,
  VGA_GREEN,
  VGA_CYAN,
  VGA_RED,
  VGA_MAGENTA,
  VGA_BROWN,
  VGA_GRAY,
  VGA_DKGRAY,
  VGA_BRIGHTBLUE,
  VGA_BRIGHTGREEN,
  VGA_BRIGHTCYAN,
  VGA_BRIGHTRED,
  VGA_BRIGHTMAGENTA,
  VGA_YELLOW,
  VGA_WHITE
};

u16 vga_mkchar (char c, enum vga_col col);
void vga_putc (int x, int y, u16 c);

#endif
