#include "config.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "fastphoto.h"
#include "cgi.h"
#include "cmd.h"
 
int
main (int argc, char * argv[])
{
  int err = 0; 
  fastphoto_t params;
  
  memset (&params, 0, sizeof (fastphoto_t));

  if (cgi_test ()) {
    err = cgi_main (&params);
  } else {
    err = cmd_main (&params, argc, argv);
  }
  
  if (params.data) free (params.data);
  
  if (err) return 1;
  else return 0;
}
