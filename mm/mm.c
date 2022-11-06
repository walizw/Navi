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

/*
 * Checks if `p1' and `p2' are the same, `count' amount of bytes.
 */
int
memcmp (void *p1, void *p2, int count)
{
  char *c1 = p1;
  char *c2 = p2;

  while (count-- > 0)
    {
      if (*c1++ != *c2++)
        return c1[-1] < c2[-1] ? -1 : 1;
    }

  return 0;
}
