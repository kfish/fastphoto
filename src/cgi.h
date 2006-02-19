#ifndef __CGI_H__
#define __CGI_H__

#include "fastphoto.h"

int cgi_test (void);

int cgi_main (fastphoto_t * params);

size_t send_memory (fastphoto_t * params);

#endif /* __CGI_H__ */
