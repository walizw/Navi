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

  char *ptr = kzalloc (4096);
  paging_set (paging_4gb_chunk_get_directory (kernel_chunk), (void *)0x1000,
              (u32)ptr | PAGING_ACCESS_FROM_ALL | PAGING_IS_PRESENT
                  | PAGING_IS_WRITEABLE);

  // enable paging
  paging_enable ();

  char *ptr2 = (char *)0x1000;
  ptr2[0] = 'A';
  ptr2[1] = 'B';
  term_print (ptr2);
  term_print (ptr);

  // enabled interrupts
  enable_interrupts ();
  term_print ("Interrupts Enabled.\n");

  return 0;
}
