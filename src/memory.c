#include <stdio.h>
#include <stdlib.h>

#include "fastphoto.h"

int
memory_init (fastphoto_t * params)
{
    params->out.name = NULL;

#if 0 /* buggy Epeg, pre-20060207 */
    if ((file_check (params->infile, NULL, &params->infile_size)) == 1) {
        params->data = malloc (params->infile_size);
        params->data_size = params->infile_size;
    }
#else
    params->data = NULL;
    params->data_size = 0;
#endif

    return 0;
}

size_t
memory_send (fastphoto_t * params)
{
    size_t n = fwrite (params->data, 1, params->data_size, stdout);
    fflush (stdout);
    return n;
}
