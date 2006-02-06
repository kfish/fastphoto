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
file_check (char * filename, time_t * mtime)
{
    struct stat statbuf;

    if (stat (filename, &statbuf) == -1) {
        switch (errno) {
            case ENOENT:
                return 0;
	    default:
		fprintf (stderr, "fastphoto: Error checking %s: %s\n", filename, strerror (errno));
		return -1;
        }
    }

    *mtime = statbuf.st_mtime;

    return 1;
}

static int
cache_check (fastphoto_t * params, char * cachefile)
{
    time_t orig_mtime, cache_mtime;
    int ret;

    if ((ret = file_check (cachefile, &cache_mtime)) != 1) {
        return ret;
    }

    if ((ret = file_check (params->infile, &orig_mtime)) != 1) {
        return ret;
    }

    if (orig_mtime > cache_mtime) {
	fprintf (stderr, "fastphoto: Removing stale cachefile %s\n", cachefile);
        unlink (cachefile);
        return 0;
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
        cachefile = alloc_snprintf ("%s%s?scale=%d%s", cachedir, path_info, params->scale, params->gray ? "&gray" : "");
    } else {
        cachefile = alloc_snprintf ("%s%s?x=%d&y=%d%s", cachedir, path_info, params->x, params->y, params->gray ? "&gray" : "");
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
