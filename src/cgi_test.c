#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#include "tests.h"

#include "fastphoto.h"
#include "cgi.h"
#include "httpdate.h"

int
main (int argc, char * argv[])
{
  fastphoto_t params;
  int err = 0;

  memset (&params, 0, sizeof (fastphoto_t));

  httpdate_init ();

  setenv ("PATH_INFO", "/TEST/test.jpg", 1);
  setenv ("PATH_TRANSLATED", "./test.jpg", 1);
  setenv ("QUERY_STRING", "width=100", 1);

  INFO("Closing standard output, so as not to blat the file at the terminal");
  INFO("Expecting fastphoto to declare a Bad file descriptor");
  close(STDOUT_FILENO);
  
  err = cgi_main (&params);

  if (params.data) free (params.data);

  if (err) return 1;
  else return 0;
}
