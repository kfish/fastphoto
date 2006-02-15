#include "config.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define CONTENT_TYPE_JPEG "Content-Type: image/jpeg\n"

int
header_content_type_jpeg ()
{
  return printf (CONTENT_TYPE_JPEG);
}

int
header_content_length (int len)
{
  return printf ("Content-Length: %d\n", len);
}

int
header_end (void)
{
  putchar('\n');
  fflush (stdout);
  return 0;
}
