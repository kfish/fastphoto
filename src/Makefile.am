# Process this file with automake to produce Makefile.in

INCLUDES = -I/usr/local/include
EPEG_LIBS = -L/usr/local/lib -lepeg

bin_PROGRAMS = fastphoto

noinst_HEADERS = resize.h

fastphoto_SOURCES = resize.c command.c
fastphoto_LDADD = $(EPEG_LIBS)
