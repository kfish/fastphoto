#include "config.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#define CONTENT_TYPE_JPEG "Content-Type: image/jpeg\n"

static char * wdays[] = {"Sun", "Mon", "Tue", "Wed", "Thu", "Fri", "Sat"};
static char * months[] = {"Jan", "Feb", "Mar", "Apr", "May", "Jun",
			  "Jul", "Aug", "Sep", "Oct", "Nov", "Dec"};

static int
http_date_snprint (char * buf, int n, time_t mtime)
{
  struct tm * g;

  g = gmtime (&mtime);

  return snprintf (buf, n, "%s, %02d %s %4d %2d:%02d:%02d GMT",
		   wdays[g->tm_wday], g->tm_mday, months[g->tm_mon],
		   g->tm_year + 1900, g->tm_hour, g->tm_min, g->tm_sec);
}

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
