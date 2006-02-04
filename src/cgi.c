#include <stdio.h>
#include <stdlib.h>

#define CONTENT_TYPE_JPEG "Content-Type: image/jpeg\n\n"

int
content_type_jpeg ()
{
    return puts (CONTENT_TYPE_JPEG);
}

int
blat (char * filename)
{
}
