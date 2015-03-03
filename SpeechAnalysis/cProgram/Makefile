# Makefile for compiling and linking the example program for generation
# of Gaussian random numbers, Randnoise.
#
# Adapt the Makefile to your installation of libsndfile. Here, it is assumed
# that libsndfile is installed in /opt/local (header files in /opt/local/include, the library
# files in /opt/local/lib).
#
CC = gcc
CFLAGS = -g -Wall -I. -I/opt/local/include
LFLAGS = -L/opt/local/lib
LIBS = -lm -lsndfile

OBJS = Randnoise.o randn.o

SRCS = Randnoise.c randn.c

all: Randnoise
	@echo 'make: Target compiled'

Randnoise: $(OBJS) $(DEPS)
	@$(CC) $(CFLAGS) -o $@ $(OBJS) $(LFLAGS) $(LIBS)

.c.o:
	@$(CC) $(CFLAGS) -c $<

clean: $(OBJS)
	@rm -f $(OBJS)
