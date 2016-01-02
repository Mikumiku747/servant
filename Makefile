#Makefile
#Builds the program

CC = gcc
CFLAGS = -g -O2
CSTD = c11

LIBS = $$(pkg-config --cflags --libs gio-2.0)

CFLAGS += -std=$(CSTD)
CFLAGS += $(LIBS)

serve: serve.h serve.c
	$(CC) $(CFLAGS) -o serve serve.h serve.c
