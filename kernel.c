/*
 * kernel.c - Navi's kernel entry point.
 *
 * Copyright (C) 2022 walizw <yojan.bustamante@udea.edu.co>
 */

#include "kernel.h"

#include <drivers/vga/term.h>

#include <idt/idt.h>

#include <mm/heap/kheap.h>
#include <mm/paging/paging.h>

/*
 * kernel paging chunk
 */
static struct paging_4gb_chunk *kernel_chunk = 0;

/*
 * Kernel entry point.
 */
int
kmain (void)
{
  term_init ();
  term_print ("Terminal Initialised.\n");

  // initialise idt
  idt_init ();
  term_print ("IDT Initialised.\n");

  // initialised heap
  kheap_init ();
  term_print ("Initialised Heap.\n");

  // setup paging
  kernel_chunk = paging_new_4gb (PAGING_IS_WRITEABLE | PAGING_IS_PRESENT
                                 | PAGING_ACCESS_FROM_ALL);
  paging_switch (paging_4gb_chunk_get_directory (kernel_chunk));

  // enable paging
  paging_enable ();

  // enabled interrupts
  enable_interrupts ();
  term_print ("Interrupts Enabled.\n");

  return 0;
}
