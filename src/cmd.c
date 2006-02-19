#include "config.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <getopt.h>

#include "fastphoto.h"

#include "memory.h"
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
    printf ("  -w, --width          Set the width of the output image\n");
    printf ("  -h, --height         Set the height of the output image\n");
    printf ("  -s, --scale          Set a percentage to scale the image by\n");
    printf ("\nOutput options\n");
    printf ("  -G, --gray, --grey   Output grayscale\n");
    printf ("  -q, --quality        Set the output quality 0-100\n");
    printf ("\nInformational options\n");
    printf ("  -i, --info           Print information about image\n");
    printf ("\nMiscellaneous options\n");
    printf ("  -H, --help           Display this help and exit\n");
    printf ("  -V, --version        Output version information and exit\n");
    printf ("\n");
}

int
cmd_main (fastphoto_t * params, int argc, char * argv[])
{
  int err = 0;
  int show_help = 0;
  int show_version = 0;
  int i;

  while (1) {
    char * optstring = "HVw:h:s:Gq:i";

#ifdef HAVE_GETOPT_LONG
    static struct option long_options[] = {
      {"help", no_argument, 0, 'H'},
      {"version", no_argument, 0, 'V'},
      {"width", required_argument, 0, 'w'},
      {"height", required_argument, 0, 'h'},
      {"scale", required_argument, 0, 's'},
      {"gray", no_argument, 0, 'G'},
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
    case 'H': /* help */
      show_help = 1;
      break;
    case 'V': /* version */
      show_version = 1;
      break;
    case 'w': /* width */
      params->x = atoi (optarg);
      break;
    case 'h': /* height */
      params->y = atoi (optarg);
      break;
    case 's': /* scale */
      params->scale = atoi (optarg);
      break;
    case 'G': /* gray */
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
    memory_send (params);
    
  return err;
}
