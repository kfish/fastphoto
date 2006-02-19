#include "config.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <getopt.h>

#include "fastphoto.h"
#include "cache.h"
#include "cgi.h"
#include "header.h"
#include "resize.h"

static void
version (void)
{
    printf ("FastPhoto " VERSION "\n");
}

static void
usage (void)
{
    printf ("Usage: fastphoto [options] infile [outfile]\n");
    printf ("Rescale a JPEG image\n");
    printf ("\nScaling options\n");
    printf ("  -x, --width          Set the width of the output image\n");
    printf ("  -y, --height         Set the height of the output image\n");
    printf ("  -s, --scale          Set a percentage to scale the image by\n");
    printf ("\nOutput options\n");
    printf ("  -g, --gray           Output grayscale\n");
    printf ("  -q, --quality        Set the output quality 0-100\n");
    printf ("\nInformational options\n");
    printf ("  -i, --info           Print information about image\n");
    printf ("\nMiscellaneous options\n");
    printf ("  -h, --help           Display this help and exit\n");
    printf ("  -v, --version        Output version information and exit\n");
    printf ("\n");
}

static int
cmd_main (fastphoto_t * params, int argc, char * argv[])
{
  int err = 0;
  int show_help = 0;
  int show_version = 0;
  int i;

  while (1) {
    char * optstring = "hvx:y:s:gq:i";

#ifdef HAVE_GETOPT_LONG
    static struct option long_options[] = {
      {"help", no_argument, 0, 'h'},
      {"version", no_argument, 0, 'v'},
      {"width", required_argument, 0, 'x'},
      {"height", required_argument, 0, 'y'},
      {"scale", required_argument, 0, 's'},
      {"gray", no_argument, 0, 'g'},
      {"quality", required_argument, 0, 'q'},
      {"info", no_argument, 0, 'i'},
      {0,0,0,0}
    };

    i = getopt_long (argc, argv, optstring, long_options, NULL);
#else
    i = getopt (argc, argv, optstring);
#endif

    if (i == -1) break;
    if (i == ':') {
      usage ();
      return 1;
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
      break;
    case 'q': /* quality */
      params->quality = atoi (optarg);
      break;
    case 'i': /* info */
      params->info = 1;
      break;
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
    usage ();
    return 1;
  }

  params->in.name = argv[optind++];

  if (optind >= argc) {
    memory_init (params);
  } else {
    params->out.name = argv[optind++];
  }

  err = resize (params);
    
  if (!err)
    send_memory (params);
    
  return err;
}

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
