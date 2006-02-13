# Process this file with automake to produce Makefile.in

AM_CFLAGS = $(EPEG_CFLAGS)

bin_PROGRAMS = fastphoto

noinst_HEADERS = alloc_snprintf.h cache.h cgi.h resize.h send.h

fastphoto_SOURCES = main.c alloc_snprintf.c cache.c cgi.c resize.c send.c
fastphoto_LDADD = $(EPEG_LIBS)
