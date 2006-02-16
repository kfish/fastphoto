#include "config.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "httpdate.h"

#define CONTENT_TYPE_JPEG "Content-Type: image/jpeg\n"

int
header_last_modified (time_t mtime)
{
  char buf[30];

  http_date_snprint (buf, 30, mtime);
  return printf ("Last-Modified: %s\n", buf);
}

int
header_content_type_jpeg ()
{
  return printf (CONTENT_TYPE_JPEG);
}

int
header_content_length (off_t len)
{
  return printf ("Content-Length: %ld\n", (long)len);
}

int
header_end (void)
{
  putchar('\n');
  fflush (stdout);
  return 0;
}
