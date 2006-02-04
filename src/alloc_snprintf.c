#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>

char *
alloc_snprintf (const char * fmt, ...)
{
  va_list ap, aq;
  char * ret;
  int n;

  va_start (ap, fmt);
  va_copy (aq, ap);

  n = vsnprintf (NULL, 0, fmt, ap); 
  ret = calloc (n+1, 1);

  vsnprintf (ret, n+1, fmt, aq);
  ret[n] = '\0';

  va_end (aq);
  va_end (ap);

  return ret;
}
