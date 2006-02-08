#include "config.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>

#if HAVE_SENDFILE
#include <errno.h>
#include <sys/sendfile.h>
#endif

#include "fastphoto.h"

#define BUFSIZE 4096

#if HAVE_SENDFILE
static int
putfile (const char * filename)
{
  int fd;
  ssize_t n;
  off_t offset = 0;

  if ((fd = open (filename, O_RDONLY)) == -1)
    goto errout;

  while ((n = sendfile (STDOUT_FILENO, fd, &offset, BUFSIZE)) != 0) {
    if (n == -1) {
      switch (errno) {
        case EAGAIN:
          break;
        default:
          goto errout;
      }
    }
  }

  close (fd);
  return 0;

errout:
  fprintf (stderr, "fastphoto: %s\n", strerror (errno));
  if (fd != -1) close (fd);
  return -1;
}
#else
static int
putfile (const char * filename)
{
  unsigned char buf[BUFSIZE];
  FILE * f;
  size_t n;

  f = fopen (filename, "rb");
  while ((n = fread (buf, 1, BUFSIZE, f)) > 0) {
      fwrite (buf, 1, n, stdout);
  }
  fclose (f);
  fflush (stdout);
  return 0;
}
#endif

size_t
send_memory (fastphoto_t * params)
{
    size_t n = fwrite (params->data, 1, params->data_size, stdout);
    fflush (stdout);
    return n;
}

int
send (fastphoto_t * params)
{
  if (params->outfile) {
    putfile (params->outfile);
  } else {
    fprintf (stderr, "fastphoto: Sending from memory ...\n");
    send_memory (params);
  }

  return 1;
}
