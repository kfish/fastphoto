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

static int
cache_check (fastphoto_t * params, char * cachefile)
{
    struct stat statbuf;

    if (stat (cachefile, &statbuf) == -1) {
        switch (errno) {
            case ENOENT:
                return 0;
	    default:
		fprintf (stderr, "fastphoto: Error checking %s; %s\n", cachefile, strerror (errno));
		return -1;
        }
    }

    params->cached = 1;

    return 1;
}

int
cache_init (fastphoto_t * params, char * path_info)
{
    char * cachedir = FASTPHOTO_DEFAULT_CACHEDIR;
    char * cachefile;
    int cached;

    if (params->scale) {
        cachefile = alloc_snprintf ("%s%s?scale=%d", cachedir, path_info, params->scale);
    } else {
        cachefile = alloc_snprintf ("%s%s?x=%d&y=%d", cachedir, path_info, params->x, params->y);
    }

    cached = cache_check (params, cachefile);

    if (cached == -1) {
    } else {
	params->outfile = cachefile;
        if (cached) {
            fprintf (stderr, "fastphoto: Using cachefile %s\n", cachefile);
	} else {
            fprintf (stderr, "fastphoto: Creating cachefile %s\n", cachefile);

            if (!mkdirs (cachefile)) {
                free (cachefile);
    	        cachefile = "/tmp/cache.jpg";
                params->outfile = cachefile;
            }
        }
    }

    return 0;
}
