#ifndef __FASTPHOTO_H__
#define __FASTPHOTO_H__

#include <sys/types.h>

#define FASTPHOTO_DEFAULT_X 128
#define FASTPHOTO_DEFAULT_Y 96

#define FASTPHOTO_DEFAULT_CACHEDIR "/var/cache/fastphoto"

typedef struct fastphoto_s fastphoto_t;
typedef struct config_s config_t;
typedef struct photo_s photo_t;

struct config_s {
  char * cachedir;
};

struct photo_s {
  char * name;
  time_t mtime;
  off_t size;
};

struct fastphoto_s {
  config_t config;

  photo_t in;
  photo_t out;

  /* If out.name == NULL, write to memory */
  unsigned char * data;
  int data_size;
  
  int nochange;
  int cached;
  int info;
  
  int x;
  int y;
  int scale;
  int quality;
  int gray;
};

#endif /* __FASTPHOTO_H__ */
