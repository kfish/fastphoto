#ifndef __CGI_H__
#define __CGI_H__

#include "fastphoto.h"

int content_type_jpeg (void);
int content_length (int len);
int cgi_end_headers (void);

int cgi_init (fastphoto_t * params);
int cgi_send (fastphoto_t * params);

#endif /* __CGI_H__ */
