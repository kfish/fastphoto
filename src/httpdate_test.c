#include <stdio.h>

#include "httpdate.h"

int
main (int argc, char * argv[])
{
  char * d_in = "Mon, 06 Feb 2006 11:20:01 GMT";
  char d_out[30];
  time_t t;

  printf ("<< Date: %s\n", d_in);
  t = httpdate_parse (d_in, 30);

  if (t == (time_t)-1) {
    printf ("** Parse error\n");
  } else {
    httpdate_snprint (d_out, 30, t);

    printf (">> Date: %s\n", d_out);
  }

  return 0;
}
