/*
 * kernel.c - Navi's kernel entry point.
 *
 * Copyright (C) 2022 walizw <yojan.bustamante@udea.edu.co>
 */

#include "kernel.h"

#include <drivers/vga/term.h>

int
kmain (void)
{
  term_init ();
  term_print ("Welcome to Navi!\nAn operating system made for fun.");

  return 0;
}
