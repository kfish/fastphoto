#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <unistd.h>

#include "fastphoto.h"
#include "photo.h"
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

static int
cache_check (fastphoto_t * params)
{
    if (params->in.mtime > params->out.mtime) {
	fprintf (stderr, "fastphoto: Removing stale cachefile %s\n", params->out.name);
        unlink (params->out.name);
        return 0;
    }

    params->cached = 1;

    return 1;
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

    photo_init (&params->out, cachefile);
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
