#ifndef __FASTPHOTO_H__
#define __FASTPHOTO_H__

#define FASTPHOTO_DEFAULT_X 128
#define FASTPHOTO_DEFAULT_Y 96

#define FASTPHOTO_DEFAULT_CACHEDIR "/var/cache/fastphoto"

typedef struct fastphoto_s fastphoto_t;

struct fastphoto_s {
    char * infile;
    char * outfile;
    int x;
    int y;
    int scale;
};

#endif /* __FASTPHOTO_H__ */
