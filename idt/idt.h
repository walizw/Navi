/*
 * idt.h - Definition of structures for the Interrupt descriptor table
 * implementation
 *
 * Copyright (C) 2022 walizw <yojan.bustamante@udea.edu.co>
 */

#ifndef __IDT_H
#define __IDT_H

#include <config.h>
#include <kernel.h>

#include <drivers/vga/term.h>

#include <mm/mm.h>

struct idt_desc
{
  u16 offset_1; // offset bits 0 - 15
  u16 selector; // selector that's in gdt
  u8 zero;      // unused
  u8 type_attr; // desc type and attributes
  u16 offset_2; // offset bits 16-31
} __attribute__ ((packed));

struct idtr_desc
{
  u16 limit; // size of descriptor table - 1
  u32 base;  // base address of the start of the interrupt descriptor table
} __attribute__ ((packed));

void idt_init ();
extern void disable_interrupts ();
extern void enable_interrupts ();

#endif
