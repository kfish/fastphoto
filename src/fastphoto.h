#ifndef __FASTPHOTO_H__
#define __FASTPHOTO_H__

typedef struct fastphoto_s fastphoto_t;

struct fastphoto_s {
    char * infile;
    char * outfile;
    int x;
    int y;
};

#endif /* __FASTPHOTO_H__ */
