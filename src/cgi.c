#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "fastphoto.h"
#include "cache.h"

#define CONTENT_TYPE_JPEG "Content-Type: image/jpeg\n"

#define BUFSIZE 4096

static void
set_param (fastphoto_t * params, char * key, char * val)
{
  if (!strcmp ("x", key)) params->x = atoi(val);
  if (!strcmp ("y", key)) params->y = atoi(val);
  if (!strcmp ("scale", key)) params->scale = atoi(val);
  if (!strcmp ("gray", key)) params->gray = 1;
  if (!strcmp ("quality", key)) params->quality = atoi(val);
  if (!strcmp ("q", key)) params->quality = atoi(val);
}

/**
 * Parse the name=value pairs in the query string and set parameters
 * @param params The fastphoto parameters to set
 * @param query The query string
 */
static void
parse_query (fastphoto_t * params, char * query)
{
  char * key, * val, * end;

  if (!query) return;

  key = query;

  do {
    val = strchr (key, '=');
    end = strchr (key, '&');

    if (end) {
      if (val) {
        if (val < end) {
          *val++ = '\0';
        } else {
          val = NULL;
        }
      }
      *end++ = '\0';
    } else {
      if (val) *val++ = '\0';
    }

    /* fprintf (stderr, "%s = %s\n", key, val);*/
    set_param (params, key, val);

    key = end;

  } while (end != NULL);

  return;
}

int
cgi_init (fastphoto_t * params)
{
  char * gateway_interface;
  char * path_info;
  char * path_translated;
  char * query_string;

  gateway_interface = getenv ("GATEWAY_INTERFACE");
  if (gateway_interface == NULL) {
    return 0;
  }

  path_info = getenv ("PATH_INFO");
  path_translated = getenv ("PATH_TRANSLATED");
  query_string = getenv ("QUERY_STRING");

  params->infile = path_translated;
  params->outfile = NULL;
  params->cached = 0;
  params->x = 0;
  params->y = 0;
  params->scale = 0;

  parse_query (params, query_string);

  cache_init (params, path_info);

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

