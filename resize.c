#include <Epeg.h>

void
resize (char * filename, int x, int y)
{
  Epeg_Image *im;

  im = epeg_file_open(filename);
  epeg_decode_size_set(im, x, y);
  epeg_file_output_set(im, "/tmp/small-fish-porn,jpg");
  epeg_encode(im);
  epeg_close(im);
}

int
main (int argc, char * argv[])
{
  char * filename;

  filename = argv[1];
  resize (filename, 128, 128);

  return 0;
}
