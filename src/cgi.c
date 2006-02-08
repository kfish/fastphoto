#include "config.h"

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
  if (!strncmp ("x", key, 2)) params->x = atoi(val);
  if (!strncmp ("width", key, 6)) params->x = atoi(val);

  if (!strncmp ("y", key, 2)) params->y = atoi(val);
  if (!strncmp ("height", key, 7)) params->y = atoi(val);

  if (!strncmp ("s", key, 2)) params->y = atoi(val);
  if (!strncmp ("scale", key, 6)) params->scale = atoi(val);

  if (!strncmp ("g", key, 2)) params->gray = 1;
  if (!strncmp ("gray", key, 5)) params->gray = 1;

  if (!strncmp ("quality", key, 8)) params->quality = atoi(val);
  if (!strncmp ("q", key, 2)) params->quality = atoi(val);
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
  params->data = NULL;
  params->data_size = 0;
  params->cached = 0;
  params->x = 0;
  params->y = 0;
  params->scale = 0;
  params->quality = 0; /* default */
  params->gray = 0;

  parse_query (params, query_string);

  cache_init (params, path_info);

  return 1;
}

int
content_type_jpeg ()
{
    puts (CONTENT_TYPE_JPEG);
    fflush (stdout);
    return 0;
}
