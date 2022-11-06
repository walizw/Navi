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

/*
 * Returns the length of a string until it's reached its null terminator, or
 * its length is greater than `max'.
 */
u32
strnlen (const char *str, u32 max)
{
  int i = 0;
  for (i = 0; i < max; i++)
    {
      if (!str[i])
        break;
    }

  return i;
}

/*
 * Returns `true' if `c' is a digit.
 */
_Bool
isdigit (char c)
{
  return c >= 48 && c <= 57;
}

/*
 * Converts `c' into a number.
 */
int
tonumericdigit (char c)
{
  return c - 48;
}
