CC = gcc
#CFLAGS = -O2 -Wall -I. -I/opt/local/include
CFLAGS = -g -Wall -I. -I/opt/local/include
LFLAGS = -L/opt/local/lib
LIBS = -lm -lsndfile
DEPS = common.h

OBJS = filtprog.o common.o

SRCS = filtprog.c common.c

all: Filter
	@echo 'make: Target compiled'

Filter: $(OBJS) $(DEPS)
	@$(CC) $(CFLAGS) -o $@ $(OBJS) $(LFLAGS) $(LIBS)

.c.o:
	@$(CC) $(CFLAGS) -c $<

clean: $(OBJS)
	@rm -f $(OBJS)
