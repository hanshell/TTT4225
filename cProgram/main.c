#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

#include "common.h"
#include "sndfile-to-float.h"
#include "get-segmentframe.h"
#include "get-length.h"
#include "gain-estimation.h"


int main(int argc, char **argv) 
{
    SNDFILE *infile;
    SF_INFO sfinfo;
    int n_pitch = 800; // number of values per frame for pitch estimate
    int n_frame = 480; // number of values per frame for LPC analysis 
    int n_step = 320;
    int n_tot_sig;
    //int n_frame_iter;
    int n_pitch_iter;
    int n_pad;
    int i;
    int offset;
    float gain;
    //int j;

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

    
    n_pad = getLength(sfinfo.frames, n_pitch, n_step, &n_pitch_iter); //returns needed padding
    n_tot_sig = (int) sfinfo.frames+n_pad; // length of signal with zero padding
    float s[(int) sfinfo.frames+n_pad]; // initialize floatingpoint signal array

    /* Elements containtan random junk
     * if not initialized to 0 */
    for (i = 0; i < n_tot_sig; i++)
    {
        s[i] = 0.0;
    }

    printf("-------\n");
    printf("Sound file %s is loaded into memory\n", argv[1]);
    printf("-------\n");
    printf("SFINFO\n");
    printf("Samplerate: %d\n", sfinfo.samplerate);
    printf("Frames: %d\n", (int)sfinfo.frames);
    printf("Channels: %d\n", sfinfo.channels);
    printf("---------\n");
    
    sndfileToFloat(infile, sfinfo.channels, &s[0]); // Sending in memloc so the func can change the arrays meomory



    /* Works fine */
    int framenr;
    offset = (n_pitch/2) - (n_frame/2); // Add a offset for the frame since it should be symmetric surrounded by the pitchframe
    for (framenr = 0; framenr < n_pitch_iter; framenr++)
    {

        float *pitch_segment = getSegmentFrame(framenr, &s[0], n_pitch, n_step, 0); // Pitch segment. Length is n_pitch
        float *sig_segment = getSegmentFrame(framenr, &s[0], n_frame, n_step, offset); // Sig segment. Length is n_frame
        
        gain = gainEstimation(&sig_segment[0], n_frame);
        printf("%f\n",gain);

        free(pitch_segment); // free momey to avoid memlacage. Have to do in in foor loop
        free(sig_segment); // free momey to avoid memlacage. Have to do in in foor loop
    }

    sf_close(infile);
    return 0;
}
