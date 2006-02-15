# Process this file with automake to produce Makefile.in

AM_CFLAGS = $(EPEG_CFLAGS)

bin_PROGRAMS = fastphoto

noinst_HEADERS = alloc_snprintf.h cache.h cgi.h header.h photo.h resize.h

fastphoto_SOURCES = main.c alloc_snprintf.c cache.c cgi.c header.c photo.c resize.c
fastphoto_LDADD = $(EPEG_LIBS)
