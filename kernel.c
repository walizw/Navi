#include "kernel.h"

#include <drivers/vga/term.h>

int
kmain (void)
{
  term_init ();
  term_print ("Welcome to Navi!\nAn operating system made for fun.");

  return 0;
}
