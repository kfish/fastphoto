#include <Epeg.h>

#include "fastphoto.h"

void
resize (fastphoto_t * params)
{
  Epeg_Image *im;
  int x, y;

  x = params->x;
  y = params->y;

  im = epeg_file_open(params->infile);
  epeg_decode_size_set(im, x, y);
  epeg_file_output_set(im, params->outfile);
  epeg_encode(im);
  epeg_close(im);
}

