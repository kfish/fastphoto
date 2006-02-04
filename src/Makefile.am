# Process this file with automake to produce Makefile.in

INCLUDES = -I/usr/local/include
EPEG_LIBS = -L/usr/local/lib -lepeg

bin_PROGRAMS = fastphoto fastphoto.cgi

noinst_HEADERS = resize.h

fastphoto_SOURCES = command.c resize.c
fastphoto_LDADD = $(EPEG_LIBS)

fastphoto_cgi_SOURCES = fastphoto.cgi.c resize.c
fastphoto_cgi_LDADD = $(EPEG_LIBS)
