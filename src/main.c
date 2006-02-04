#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "fastphoto.h"
#include "cgi.h"
#include "resize.h"

int
main (int argc, char * argv[])
{
  int cgi = 0; 
  fastphoto_t params;

  memset (&params, 1, sizeof (fastphoto_t));

  if (cgi_init(&params)) {
    cgi = 1;
    content_type_jpeg ();
  } else {
    params.infile = argv[1];
    params.outfile = argv[2];
    params.x = 128;
    params.y = 128;
  }

  resize (&params);

  if (cgi) {
    cgi_send (&params);
  }

  return 0;
}
