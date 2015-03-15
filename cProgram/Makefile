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

DEPS = common.h sndfile-to-float.h hamming.h autocorr_lpc.h get-segmentframe.h get-length.h gain-estimation.h voice_classification.h decimation.h interpolation.h signal_rectification.h Randnoise.h filter.h

#headerfiles which have been made by  

OBJS = main.o common.o sndfile-to-float.o hamming.o autocorr_lpc.o get-segmentframe.o get-length.o gain-estimation.o voice_classification.o decimation.o interpolation.o signal_rectification.o Randnoise.o randn.o filter.o


SRCS = main.c common.c sndfile-to-float.c hamming.c autocorr_lpc.c get-segmentframe.c get-length.c gain-estimation.c voice_classification.c decimation.c interpolation.c signal_rectification.c Randnoise.c randn.c filter.c

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
