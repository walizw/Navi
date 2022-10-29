#ifndef __TERM_H
#define __TERM_H

#include "vga.h"

#include <string/string.h>

void term_init ();
void term_writec (char c, enum vga_col color);
void term_print (const char *str);

#endif
