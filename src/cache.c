#include "fastphoto.h"

int
cache_init (fastphoto_t * params)
{
    params->outfile = "/tmp/cache.jpg";
    return 0;
}
