#include <stdio.h>
#include <Epeg.h>

#include "fastphoto.h"

int
resize (fastphoto_t * params)
{
  Epeg_Image *im;
  int x, y, w, h, scale;
  const char * comment;

  im = epeg_file_open(params->infile);
  if (im == NULL) return -1;

  epeg_size_get (im, &w, &h);

  if (params->info) {
    printf ("%s:\tJPEG image, %dx%d\n", params->infile, w, h);
    comment = epeg_comment_get (im);
    if (comment) printf ("  Comment: %s\n", comment);
    goto im_close;
  }

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

  if (params->outfile)
    epeg_file_output_set(im, params->outfile);
  else if (params->data)
    epeg_memory_output_set (im, &params->data, &params->data_size);

  epeg_encode(im);

im_close:
  epeg_close(im);

  return 0;
}
