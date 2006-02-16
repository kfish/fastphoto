# Process this file with automake to produce Makefile.in

AM_CFLAGS = $(EPEG_CFLAGS)

bin_PROGRAMS = fastphoto
noinst_PROGRAMS = httpdate_test

noinst_HEADERS = alloc_snprintf.h cache.h cgi.h header.h httpdate.h photo.h resize.h

fastphoto_SOURCES = main.c alloc_snprintf.c cache.c cgi.c header.c httpdate.c photo.c resize.c
fastphoto_LDADD = $(EPEG_LIBS)

httpdate_test_SOURCES = httpdate.c httpdate_test.c