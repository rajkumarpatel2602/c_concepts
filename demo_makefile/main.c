#include <stdio.h>
#include <foo1.h>
#include <foo2.h>


int
main (void)
{
  printf ("inside main!\n");

  //call function belong to static lib
  foo1 ();
  foo2 ();
}
