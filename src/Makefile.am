# Process this file with automake to produce Makefile.in

AM_CFLAGS = $(EPEG_CFLAGS)

bin_PROGRAMS = fastphoto
noinst_PROGRAMS = httpdate_test cgi_test

TESTS_ENVIRONMENT = $(VALGRIND_ENVIRONMENT)

TESTS = httpdate_test cgi_test

noinst_HEADERS = fastphoto.h alloc_snprintf.h cache.h cgi.h cmd.h read_config.h header.h httpdate.h memory.h photo.h resize.h tests.h xini.h

fastphoto_SOURCES = main.c alloc_snprintf.c cache.c cgi.c cmd.c read_config.c header.c httpdate.c memory.c photo.c resize.c xini.c
fastphoto_LDADD = $(EPEG_LIBS)

httpdate_test_SOURCES = httpdate.c httpdate_test.c

cgi_test_SOURCES = cgi_test.c cgi.c alloc_snprintf.c cache.c read_config.c httpdate.c header.c photo.c resize.c memory.c xini.c
cgi_test_LDADD = $(EPEG_LIBS)
