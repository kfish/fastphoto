#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "fastphoto.h"
#include "cgi.h"
#include "resize.h"

#define CONTENT_TYPE_JPEG "Content-Type: image/jpeg\n\n"

int
main (int argc, char * argv[])
{
  fastphoto_t params;

  memset (&params, 1, sizeof (fastphoto_t));

  if (cgi_init(&params)) {

  } else {
    params.infile = argv[1];
    params.outfile = argv[2];
    params.x = 128;
    params.y = 128;
  }

  resize (&params);

  return 0;
}
