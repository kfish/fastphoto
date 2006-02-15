#ifndef __CACHE_H__
#define __CACHE_H__

int cache_init (fastphoto_t * params, char * path_info);

int memory_init (fastphoto_t * params);
int memory_send (fastphoto_t * params);

int file_check (char * filename, time_t * mtime, off_t * size);

#endif /* __CACHE_H__ */
