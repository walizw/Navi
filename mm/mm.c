/*
 * mm.c - Generic and simple memory management functions.
 *
 * Copyright (C) 2022 walizw <yojan.bustamante@udea.edu.co>
 */

void *
memset (void *ptr, int c, unsigned long size)
{
  char *c_ptr = (char *)ptr;
  for (int i = 0; i < size; i++)
    {
      c_ptr[i] = (char)c;
    }
  return ptr;
}
