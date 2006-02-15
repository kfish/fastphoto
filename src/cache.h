#ifndef __CACHE_H__
#define __CACHE_H__

int cache_init (fastphoto_t * params, char * path_info);

int memory_init (fastphoto_t * params);
int memory_send (fastphoto_t * params);

int file_check (photo_t * photo);


#endif /* __CACHE_H__ */
