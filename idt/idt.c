/*
 * idt.c - Implementation of the Interrupt descriptor table. Notice that here
 * are also declared the interrupts that are not part of the 0x80 interrupt.
 *
 * Copyright (C) 2022 walizw <yojan.bustamante@udea.edu.co>
 */

#include "idt.h"
#include "config.h"

extern void idt_load (struct idtr_desc *ptr);

struct idt_desc idt_descriptors[NAVI_TOTAL_INTERRUPTS];
struct idtr_desc idtr_descriptor;

void
idt_zero ()
{
  term_print ("Divide by zero error\n");
}

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

void
idt_init ()
{
  memset (idt_descriptors, 0, sizeof (idt_descriptors));
  idtr_descriptor.limit = sizeof (idt_descriptors) - 1;
  idtr_descriptor.base = (u32)idt_descriptors;

  // set the interrupts before the idt is loaded
  idt_set (0, idt_zero);

  // load the idt
  idt_load (&idtr_descriptor);
}
