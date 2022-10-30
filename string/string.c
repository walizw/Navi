/*
 * string.c - Generic functions for string/memory management.
 *
 * Copyright (C) 2022 walizw <yojan.bustamante@udea.edu.co>
 */

#include "string.h"

/*
 * Returns the length of a string.
 */
u32
strlen (const char *str)
{
  u32 len = 0;
  while (str[len])
    {
      len++;
    }
  return len;
}
