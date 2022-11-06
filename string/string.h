/*
 * string.h - Generic functions for string/memory management.
 *
 * Copyright (C) 2022 walizw <yojan.bustamante@udea.edu.co>
 */

#ifndef __STRING_H
#define __STRING_H

#include <kernel.h>

u32 strlen (const char *str);
u32 strnlen (const char *str, u32 max);
_Bool isdigit (char c);
int tonumericdigit (char c);

#endif
