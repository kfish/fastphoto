#include "config.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "fastphoto.h"
#include "cache.h"
#include "header.h"
#include "httpdate.h"
#include "memory.h"
#include "photo.h"
#include "resize.h"

static void
set_param (fastphoto_t * params, char * key, char * val)
{
  if (!strncmp ("w", key, 2)) params->x = atoi(val);
  if (!strncmp ("width", key, 6)) params->x = atoi(val);

  if (!strncmp ("h", key, 2)) params->y = atoi(val);
  if (!strncmp ("height", key, 7)) params->y = atoi(val);

  if (!strncmp ("s", key, 2)) params->y = atoi(val);
  if (!strncmp ("scale", key, 6)) params->scale = atoi(val);

  if (!strncmp ("gray", key, 5)) params->gray = 1;
  if (!strncmp ("grey", key, 5)) params->gray = 1;

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
cgi_test (void)
{
  char * gateway_interface;

  gateway_interface = getenv ("GATEWAY_INTERFACE");
  if (gateway_interface == NULL) {
    return 0;
  }

  return 1;
}

static int
cgi_send_photo (photo_t * photo)
{
  header_content_length (photo->size);
  header_end();

  photo_put (photo);

  return 0;
}

static int
cgi_send (fastphoto_t * params)
{
  header_last_modified (params->in.mtime);

  if (params->nochange) {
    cgi_send_photo (&params->in);
  } else if (params->out.name) {
    cgi_send_photo (&params->out);
  } else {
    header_content_length ((off_t)params->data_size);
    header_end();

    memory_send (params);
  }

  return 0;
}

int
cgi_main (fastphoto_t * params)
{
  int err = 0;
  char * path_info;
  char * path_translated;
  char * query_string;
  char * if_modified_since;
  time_t since_time;

  httpdate_init ();

  path_info = getenv ("PATH_INFO");
  path_translated = getenv ("PATH_TRANSLATED");
  query_string = getenv ("QUERY_STRING");
  if_modified_since = getenv ("HTTP_IF_MODIFIED_SINCE");

  photo_init (&params->in, path_translated);

  if (if_modified_since != NULL) {
    int len;

    fprintf (stderr, "If-Modified-Since: %s\n", if_modified_since);

    len = strlen (if_modified_since) + 1;
    since_time = httpdate_parse (if_modified_since, len);

    if (params->in.mtime <= since_time) {
      header_not_modified();
      header_end();
      return 1;
    }
  }

  header_content_type_jpeg ();

  parse_query (params, query_string);

  if (params->x || params->y || params->scale || params->gray ||
      params->quality) {
    cache_init (params, path_info);
  } else {
    params->nochange = 1;
  }

  err = 0;
  if (!(params->nochange || params->cached)) {
    err = resize (params);
  }
  
  if (!err) {
    cgi_send (params);
  }

  return err;
}
