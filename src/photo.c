#include "config.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <errno.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>

#if HAVE_SENDFILE
#include <sys/sendfile.h>
#endif

#include "fastphoto.h"
#include "cgi.h"
#include "header.h"

#define BUFSIZE 4096

int
photo_init (photo_t * photo, char * name)
{
  struct stat statbuf;

  photo->name = name;

  if (stat (name, &statbuf) == -1) {
    switch (errno) {
    case ENOENT:
      return 0;
    default:
      fprintf (stderr, "fastphoto: Error checking %s: %s\n", name, strerror (errno));
      return -1;
    }
  }
  
  photo->mtime = statbuf.st_mtime;
  photo->size = statbuf.st_size;
  
  return 1;
}

#if HAVE_SENDFILE
int
photo_put (photo_t * photo)
{
  int fd;
  ssize_t n;
  off_t offset = 0;

  if ((fd = open (photo->name, O_RDONLY)) == -1)
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
int
photo_put (photo_t * photo)
{
  unsigned char buf[BUFSIZE];
  FILE * f;
  size_t n;

  f = fopen (photo->name, "rb");
  while ((n = fread (buf, 1, BUFSIZE, f)) > 0) {
      fwrite (buf, 1, n, stdout);
  }
  fclose (f);
  fflush (stdout);
  return 0;
}
#endif
