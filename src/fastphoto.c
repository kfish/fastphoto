#include <stdio.h>
#include <stdlib.h>

#include "cgi.h"
#include "resize.h"

#define CONTENT_TYPE_JPEG "Content-Type: image/jpeg\n\n"

int
main (int argc, char * argv[])
{
  char * infile, * outfile;
  char * query_string;

  content_type_jpeg ();

  query_string = getenv ("QUERY_STRING");

  infile = getenv ("PATH_TRANSLATED");
  outfile = "/tmp/cache.jpg";
  resize (infile, outfile, 128, 128);

  return 0;
}
