#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>

#include "fastphoto.h"
#include "xini.h"

static XiniStatus
config_section (const char * name, void * user_data)
{
  return XINI_OK;
}

static XiniStatus
config_assign (const char * name, const char * value, void * user_data)
{
  config_t * config = (config_t *) user_data;

  fprintf (stderr, "CONFIG: %s = %s\n", name, value); 

  if (!strncmp (name, "cachedir", 8)) {
    config->cachedir = strdup (value);
  }

  return XINI_OK;
}

static int
config_read (config_t * config, const char * path)
{
  XiniStatus status;

  fprintf (stderr, "CONFIG: Reading %s\n", path);

  status = xini_read (path, config_section, config, config_assign, config);

  fprintf (stderr, "CONFIG: status %d\n", status);

  return (status == XINI_OK) ? 0 : -1;
}

int
config_init (config_t * config)
{
  config->cachedir = FASTPHOTO_DEFAULT_CACHEDIR;

  config_read (config, "/etc/fastphoto/fastphoto.ini");
}
