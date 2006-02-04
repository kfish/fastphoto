#include <Epeg.h>

void
resize (char * infile, char * outfile, int x, int y)
{
  Epeg_Image *im;

  im = epeg_file_open(infile);
  epeg_decode_size_set(im, x, y);
  epeg_file_output_set(im, outfile);
  epeg_encode(im);
  epeg_close(im);
}

