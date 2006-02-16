#include "config.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

static char * wdays[] = {"Sun", "Mon", "Tue", "Wed", "Thu", "Fri", "Sat"};
static char * months[] = {"Jan", "Feb", "Mar", "Apr", "May", "Jun",
			  "Jul", "Aug", "Sep", "Oct", "Nov", "Dec"};

int
http_date_snprint (char * buf, int n, time_t mtime)
{
  struct tm * g;

  g = gmtime (&mtime);

  return snprintf (buf, n, "%s, %02d %s %4d %2d:%02d:%02d GMT",
		   wdays[g->tm_wday], g->tm_mday, months[g->tm_mon],
		   g->tm_year + 1900, g->tm_hour, g->tm_min, g->tm_sec);
}
