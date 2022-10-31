/*
 * mm.c - Generic and simple memory management functions.
 *
 * Copyright (C) 2022 walizw <yojan.bustamante@udea.edu.co>
 */

#include "mm.h"

/*
 * Sets the value of `ptr' of `c' by a specified size.
 */
void *
memset (void *ptr, int c, u32 size)
{
  char *c_ptr = (char *)ptr;
  for (int i = 0; i < size; i++)
    {
      c_ptr[i] = (char)c;
    }
  return ptr;
}
