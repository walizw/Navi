/*
 * kernel.c - Navi's kernel entry point.
 *
 * Copyright (C) 2022 walizw <yojan.bustamante@udea.edu.co>
 */

#include "kernel.h"

#include <drivers/vga/term.h>

#include <idt/idt.h>
#include <mm/heap/kheap.h>

/*
 * Kernel entry point.
 */
int
kmain (void)
{
  term_init ();
  term_print ("Terminal Initialised.\n");

  idt_init ();
  term_print ("IDT Initialised.\n");

  kheap_init ();
  term_print ("Enabled Heap.\n");

  enable_interrupts ();
  term_print ("Interrupts Enabled.\n");

  return 0;
}
