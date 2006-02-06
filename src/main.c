#include "config.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <getopt.h>

#include "fastphoto.h"
#include "cgi.h"
#include "resize.h"

static void
version (void)
{
    printf ("FastPhoto " VERSION "\n");
}

static void
usage (void)
{
    printf ("Usage: fastphoto [options] infile outfile\n");
    printf ("Resize a JPEG image\n\n");
    printf ("Options\n");
    printf ("  -x, --width          Set the width of the output image\n");
    printf ("  -y, --height         Set the height of the output image\n");
    printf ("  -s, --scale          Set a percentage to scale the image by\n");
    printf ("  -g, --gray           Output grayscale\n");
    printf ("\n");
}

static int
cmd_init (fastphoto_t * params, int argc, char * argv[])
{
    int show_help = 0;
    int show_version = 0;
    int i;

    params->cached = 0;
    params->x = 0;
    params->y = 0;
    params->scale = 0;
    params->gray = 0;

    while (1) {
        char * optstring = "hvx:y:s:g";

#ifdef HAVE_GETOPT_LONG
	static struct option long_options[] = {
            {"help", no_argument, 0, 'h'},
            {"version", no_argument, 0, 'v'},
            {"width", required_argument, 0, 'x'},
            {"height", required_argument, 0, 'y'},
            {"scale", required_argument, 0, 's'},
            {"gray", no_argument, 0, 'g'},
	    {0,0,0,0}
	};

	i = getopt_long (argc, argv, optstring, long_options, NULL);
#else
	i = getopt (argc, argv, optstring);
#endif

	if (i == -1) break;
	if (i == ':') {
            return -1;
        }

	switch (i) {
        case 'h': /* help */
            show_help = 1;
            break;
        case 'v': /* version */
            show_version = 1;
            break;
        case 'x': /* width */
            params->x = atoi (optarg);
            break;
        case 'y': /* height */
            params->y = atoi (optarg);
            break;
        case 's': /* scale */
            params->scale = atoi (optarg);
            break;
	case 'g': /* gray */
	    params->gray = 1;
	default:
            break;
        }

    }

    if (show_version) {
        version ();
    }

    if (show_help) {
        usage ();
    }

    if (show_version || show_help) {
        return 0;
    }

    if (optind >= argc) {
        return -1;
    }

    params->infile = argv[optind++];
    params->outfile = argv[optind++];

    return 1;
}

int
main (int argc, char * argv[])
{
    int cgi = 0, err = 0; 
    fastphoto_t params;
  
    memset (&params, 0, sizeof (fastphoto_t));
  
    if (cgi_init(&params)) {
        cgi = 1;
        content_type_jpeg ();
    } else {
	err = cmd_init(&params, argc, argv);

	if (err == 0) {
            /* Just handled --help or --version */
	    exit (0);
	} else if (err == -1) {
            /* Usage error */
            usage ();
            exit (1);
        }
    }
  
    if (!params.cached) {
        resize (&params);
    }
  
    if (cgi) {
        cgi_send (&params);
    }
  
    return 0;
}
