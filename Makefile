#gcc resize.c -I/usr/local/include -L /usr/local/lib -lepeg -o resize

INCLUDES= -I/usr/local/include
LDFLAGS= -L/usr/local/lib -lepeg

all: resize

resize: resize.o command.o
