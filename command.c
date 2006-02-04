
#include "resize.h"

int
main (int argc, char * argv[])
{
  char * filename;

  filename = argv[1];
  resize (filename, 128, 128);

  return 0;
}
