#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <unistd.h>

#include "fastphoto.h"
#include "alloc_snprintf.h"

#define PATH_SEP '/'

static int
mkdirs (char * path)
{
    char * s, * sep;
    int active = 1;

    s = path;
    if (*s == '/') s++;
    sep = strchr (s, PATH_SEP);
    while (active && sep != NULL) {
	/* NUL terminate at separator */
        *sep = '\0';

        if (mkdir (path, 0700) == -1) {
            switch (errno) {
                case EEXIST:
                    break;
                default:
                    fprintf (stderr, "fastphoto: Error creating %s: %s\n", path, strerror (errno));
		    active = 0;
	    }
	}

	*sep = PATH_SEP;
	s = sep;
	s++;
	sep = strchr (s, PATH_SEP);
    }

    return active;
}

int
file_check (photo_t * photo)
{
    struct stat statbuf;

    if (stat (photo->name, &statbuf) == -1) {
        switch (errno) {
            case ENOENT:
                return 0;
	    default:
		fprintf (stderr, "fastphoto: Error checking %s: %s\n", photo->name, strerror (errno));
		return -1;
        }
    }

    photo->mtime = statbuf.st_mtime;
    photo->size = statbuf.st_size;

    return 1;
}

static int
cache_check (fastphoto_t * params)
{
    int ret;

    if ((ret = file_check (&params->out)) != 1) {
        return ret;
    }

    if ((ret = file_check (&params->in)) != 1) {
        return ret;
    }

    if (params->in.mtime > params->out.mtime) {
	fprintf (stderr, "fastphoto: Removing stale cachefile %s\n", params->out.name);
        unlink (params->out.name);
        return 0;
    }

    params->cached = 1;

    return 1;
}

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

int
cache_init (fastphoto_t * params, char * path_info)
{
    char * cachedir = FASTPHOTO_DEFAULT_CACHEDIR;
    char * cachefile, * c;
    int cached;

    if (params->scale) {
        cachefile = alloc_snprintf ("%s%s?scale=%d", cachedir, path_info, params->scale);
    } else {
        cachefile = alloc_snprintf ("%s%s?x=%d&y=%d", cachedir, path_info, params->x, params->y);
    }

    if (params->quality) {
        c = alloc_snprintf ("%s&q=%d", cachefile, params->quality);
	free (cachefile);
	cachefile = c;
    }

    if (params->gray) {
	c = alloc_snprintf ("%s&gray", cachefile);
	free (cachefile);
	cachefile = c;
    }

    params->out.name = cachefile;
    cached = cache_check (params);

    if (cached == -1) {
      params->out.name = NULL;
    } else {
        if (cached) {
            fprintf (stderr, "fastphoto: Using cachefile %s\n", cachefile);
	} else {
            fprintf (stderr, "fastphoto: Creating cachefile %s\n", cachefile);

            if (!mkdirs (cachefile)) {
                fprintf (stderr, "fastphoto: Error creating cachefile %s\n", cachefile);
                free (cachefile);

		memory_init (params);
            }
        }
    }

    return 0;
}
