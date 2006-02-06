#ifndef __FASTPHOTO_H__
#define __FASTPHOTO_H__

#include <sys/types.h>

#define FASTPHOTO_DEFAULT_X 128
#define FASTPHOTO_DEFAULT_Y 96

#define FASTPHOTO_DEFAULT_CACHEDIR "/var/cache/fastphoto"

typedef struct fastphoto_s fastphoto_t;

struct fastphoto_s {
    char * infile;
    char * outfile;

    off_t infile_size;
    /* If outfile == NULL, write to memory */
    unsigned char * data;
    int data_size;

    int cached;
    int info;

    int x;
    int y;
    int scale;
    int quality;
    int gray;
};

#endif /* __FASTPHOTO_H__ */
