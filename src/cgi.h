#ifndef __CGI_H__
#define __CGI_H__

#include "fastphoto.h"

int cgi_init (fastphoto_t * params);
int cgi_send (fastphoto_t * params);

size_t send_memory (fastphoto_t * params);

#endif /* __CGI_H__ */
