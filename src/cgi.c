#include <stdio.h>
#include <stdlib.h>

#include "fastphoto.h"

#define CONTENT_TYPE_JPEG "Content-Type: image/jpeg\n"

#define BUFSIZE 4096

static char * path_translated;
static char * query_string;

int
cgi_init (fastphoto_t * params)
{
  char * gateway_interface;

  gateway_interface = getenv ("GATEWAY_INTERFACE");
  if (gateway_interface == NULL) {
    return 0;
  }

  path_translated = getenv ("PATH_TRANSLATED");
  query_string = getenv ("QUERY_STRING");

  params->infile = path_translated;
  params->outfile = "/tmp/cache.jpg";
  params->x = 128;
  params->y = 128;

  return 1;
}

int
content_type_jpeg ()
{
    return puts (CONTENT_TYPE_JPEG);
}

int
cgi_send (fastphoto_t * params)
{
    unsigned char buf[BUFSIZE];
    FILE * fd;
    size_t n;

    fd = fopen (params->outfile, "rb");
    while ((n = fread (buf, 1, BUFSIZE, fd)) > 0) {
        fwrite (buf, 1, n, stdout);
    }
    fclose (fd);

    return 1;
}

