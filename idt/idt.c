/*
 * idt.c - Implementation of the Interrupt descriptor table. Notice that here
 * are also declared the interrupts that are not part of the 0x80 interrupt.
 *
 * Copyright (C) 2022 walizw <yojan.bustamante@udea.edu.co>
 */

#include "idt.h"
#include <config.h>

#include <io/io.h>

extern void idt_load (struct idtr_desc *ptr);

extern void int21h ();
extern void no_interrupt ();

struct idt_desc idt_descriptors[NAVI_TOTAL_INTERRUPTS];
struct idtr_desc idtr_descriptor;

/*
 * The int21h (pic irq 1) handler
 */
void
int21h_handler ()
{
  term_print ("keyboard pressed\n");
  outb (0x20, 0x20);
}

/*
 * All the interrupts will come here, where they'll just be acknowledged.
 */
void
no_interrupt_handler ()
{
  outb (0x20, 0x20);
}

/*
 * The 0x00 interrupt (division by zero exception)
 */
void
idt_zero ()
{
  term_print ("Divide by zero error\n");
}

/*
 * Sets a single interrupt in the idt to `addr'
 */
void
idt_set (int i, void *addr)
{
  struct idt_desc *desc = &idt_descriptors[i];
  desc->offset_1 = (u32)addr & 0x0000ffff;
  desc->selector = NAVI_KERNEL_CODE_SELECTOR;
  desc->zero = 0x00;
  desc->type_attr = 0xEE;
  desc->offset_2 = (u32)addr >> 16;
}

/*
 * Initialises the IDT
 */
void
idt_init ()
{
  memset (idt_descriptors, 0, sizeof (idt_descriptors));
  idtr_descriptor.limit = sizeof (idt_descriptors) - 1;
  idtr_descriptor.base = (u32)idt_descriptors;

  for (int i = 0; i < NAVI_TOTAL_INTERRUPTS; i++)
    {
      idt_set (i, no_interrupt);
    }

  // set the interrupts before the idt is loaded
  idt_set (0, idt_zero);
  idt_set (0x21, int21h);

  // load the idt
  idt_load (&idtr_descriptor);
}
