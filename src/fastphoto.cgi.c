#include <stdio.h>
#include <stdlib.h>

#include "resize.h"

#define CONTENT_TYPE_JPEG "Content-Type: image/jpeg\n\n"

int
content_type_jpeg ()
{
    return puts (CONTENT_TYPE_JPEG);
}

int
main (int argc, char * argv[])
{
  char * infile, * outfile;
  char * query_string;

  content_type_jpeg ();

  query_string = getenv ("QUERY_STRING");

  infile = argv[1];
  outfile = argv[2];
  resize (infile, outfile, 128, 128);

  return 0;
}
