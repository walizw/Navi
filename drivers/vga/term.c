/*
 * term.c - A very basic "terminal" helper to print out stuff to the screen.
 *
 * Copyright (C) 2022 walizw <yojan.bustamante@udea.edu.co>
 */

#include "term.h"

u16 row = 0;
u16 col = 0;

void
term_init ()
{
  row = 0;
  col = 0;

  for (int y = 0; y < VGA_HEIGHT; y++)
    {
      for (int x = 0; x < VGA_WIDTH; x++)
        {
          vga_putc (x, y, 0);
        }
    }
}

void
term_writec (char c, enum vga_col color)
{
  if (c == '\n')
    {
      row += 1;
      col = 0;
      return;
    }

  vga_putc (col, row, vga_mkchar (c, color));
  col += 1;

  if (col >= VGA_WIDTH)
    {
      col = 0;
      row += 1;
    }
}

void
term_print (const char *str)
{
  u32 len = strlen (str);
  for (u32 i = 0; i < len; i++)
    {
      term_writec (str[i], VGA_WHITE);
    }
}
