#include "config.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "fastphoto.h"
#include "cgi.h"
#include "resize.h"

static void
usage (void)
{
    printf ("FastPhoto " VERSION "\n");
    printf ("Usage: fastphoto infile outfile\n");
}

int
main (int argc, char * argv[])
{
    int cgi = 0; 
    fastphoto_t params;
  
    memset (&params, 0, sizeof (fastphoto_t));
  
    if (cgi_init(&params)) {
        cgi = 1;
        content_type_jpeg ();
    } else {
	if (argc < 3) {
	    usage ();
	    exit (1);
	}

        params.infile = argv[1];
        params.outfile = argv[2];
        params.x = 128;
        params.y = 128;
    }
  
    resize (&params);
  
    if (cgi) {
	/*
        puts ("Content-Type: text/plain\n\n");
        printf ("Infile: %s\n", params.infile);
        printf ("Outfile: %s\n", params.outfile);
	*/
        cgi_send (&params);
    }
  
    return 0;
}
