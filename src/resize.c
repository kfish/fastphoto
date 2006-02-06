#include <Epeg.h>

#include "fastphoto.h"

void
resize (fastphoto_t * params)
{
  Epeg_Image *im;
  int x, y, w, h, scale;

  im = epeg_file_open(params->infile);

  epeg_size_get (im, &w, &h);

  x = params->x;
  y = params->y;

  if (x == 0 && y == 0) {
    if ((scale = params->scale) == 0) {
        x = w;
        y = h;
    } else {
	x = w * scale / 100;
	y = h * scale / 100;
    }
  } else if (x == 0) {
    x = w*y/h;
  } else if (y == 0) {
    y = h*x/w;
  }
  epeg_decode_size_set(im, x, y);

  if (params->gray)
    epeg_decode_colorspace_set (im, EPEG_GRAY8);

  if (params->quality)
    epeg_quality_set (im, params->quality);

  epeg_file_output_set(im, params->outfile);
  epeg_encode(im);
  epeg_close(im);
}

