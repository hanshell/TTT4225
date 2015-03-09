#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

#include "common.h"
#include "sndfile-to-float.h"
#include "get-frame.h"


int main(int argc, char **argv) 
{
    SNDFILE *infile;
    SF_INFO sfinfo;

    /* Allocate and initialize memory, and open the input file  
       memset(void *str, int c, size_t n) 
       str is pointer to the block of meomory to fill
       c value to be set. 
       n is the number of bytes to be set to the value*/
    memset (&sfinfo, 0, sizeof (sfinfo)) ;
    // argv [1] is first parameter given to output func
    if ((infile = sf_open (argv [1], SFM_READ, &sfinfo)) == NULL)
    { printf ("Error : Not able to open input file '%s'\n", argv [1]) ;
        sf_close (infile) ;
        exit (1) ;
    } 
    /* If the source is stereo, inform that it will be mixed down to mono */ 
    if (sfinfo.channels != 1)
    { printf ("Input file '%s' not mono. Will mix to single channel.\n", argv [1]) ;
    } ;

    float s[(int) sfinfo.frames];

    printf("-------\n");
    printf("Sound file %s is loaded into memory\n", argv[1]);
    printf("-------\n");
    printf("SFINFO\n");
    printf("Samplerate: %d\n", sfinfo.samplerate);
    printf("Frames: %d\n", (int)sfinfo.frames);
    printf("Channels: %d\n", sfinfo.channels);

    sndfileToFloat(infile, sfinfo.channels, &s[0]);

    /* Works fine */
    int framenr = 1;
    float *segment = getFrame(framenr, &s[0], 480, 320);
    int k;
    for (k = 0; k < 480; k++)
    {
        printf("TEST: %d\t\t%f\n", (framenr*480+k),segment[k]);
    }

    free(segment);
    sf_close(infile);
    return 0;
}
