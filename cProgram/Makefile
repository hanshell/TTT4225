# Defines which compiler to use0i
CC=gcc
# Debugging flags. Purpose -> include debugging info into the executable file
# Can then use gdb to debug code
DEBUG = -g
# Flags used in compiling and creating object files, -c option needed to create object files
# -> the .o files
CFLAGS= -Wall -I. -I/opt/local/include
# Linking flags. Dont reakky need any special flags for linking. But useing -Wall 
# teller compiler tro print all warnings
LFLAGS= -Wall -L/opt/local/lib
LIBS = -lm -lsndfile

DEPS = common.h sndfile-to-float.h get-frame.h
#headerfiles which have been made by  


OBJS = main.o common.o sndfile-to-float.o get-frame.o
SRCS = main.c common.c sndfile-to-float.c get-frame.h


all: Main
	@echo 'make: Target compiled'

#$@ is the name of the target currently being processed
#$< is the name of the first dependency
Main : $(OBJS) $(DEPS) 
	@$(CC) $(CFLAGS) -o $@ $(OBJS) $(LFLAGS) $(LIBS)

.c.o:
	@$(CC) $(CFLAGS) -c $<


# Should not be necessary if macefile is created properly.
# forces recompiling of the files with object files
#  backslash prevents rm from complaining.
clean: 
	@rm -f $(OBJS)
