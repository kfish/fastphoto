
#include "resize.h"

int
main (int argc, char * argv[])
{
  char * infile, * outfile;

  infile = argv[1];
  outfile = argv[2];
  resize (infile, outfile, 128, 128);

  return 0;
}
