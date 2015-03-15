#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

#include "common.h"
#include "sndfile-to-float.h"
#include "get-segmentframe.h"
#include "get-length.h"
#include "gain-estimation.h"
#include "hamming.h"
#include "Randnoise.h"
#include "overlapAdd.h"
#include "voice_classification.h"
#include "autocorr_lpc.h"
#include "filter.h"


int main(int argc, char **argv) 
{

    SNDFILE *infile;
    SF_INFO sfinfo;
    int n_pitch = 800; // number of values per frame for pitch estimate
    int n_frame = 480; // number of values per frame for LPC analysis 
    int n_step = 320;
    int n_tot_sig; // total signal including zeropadding
    //int n_frame_iter;
    int n_pitch_iter; //number of iterations we have to loop over the soundfile
    int n_pad; //number of zeroes we have to pad with
    int i;
    int offset; // offset to keep centering inside the pitchframe
    float gain; // const to multiply something with
    //int prev_voiced = 0; // if previ segment was voiced or not
    //float *out_float; // Containing full output signal in float
    float *lpc_coeffs;
    int pitch_period;

    //int *prev_pitch_pos;
    //*prev_pitch_pos = 0;
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



    n_pitch_iter = 19;
    /* Works fine */
    int framenr;
    offset = (n_pitch/2) - (n_frame/2); // Add a offset for the frame since it should be symmetric surrounded by the pitchframe
    for (framenr = 18; framenr < n_pitch_iter; framenr++) // Loop oper every segment and to stuff
    {

        // Get segments for pitchestimation and LPC analysis
        float *pitch_segment = getSegmentFrame(framenr, &s[0], n_pitch, n_step, 0); // Pitch segment. Length is n_pitch
        float *sig_segment = getSegmentFrame(framenr, &s[0], n_frame, n_step, offset); // Sig segment. Length is n_frame
        //////////// TESTED //////////////////



        // Apply hamming window to signal 
        float *pitch_ham = hamming_window(pitch_segment, n_pitch);
        float *sig_ham = hamming_window(sig_segment, n_frame);
        /////////////// TESTED ///////////////

        //for (i = 0; i < n_pitch; i++) {
        //    printf("%f\n", pitch_ham[i]);

        //}

        float *corr = autocorrelation(pitch_ham, n_pitch);
        for (i = 0; i < n_pitch; i++) {
            printf("%f\n", corr[i]);

        }
        free(corr);
        //get lpc coefficients -> gives almost the same coeffs as matlab
        //All numbers have opposite sign from matlab
        lpc_coeffs = levinson_durbin_recursion(&sig_ham[0], 14, n_frame);
        for (i = 1; i < 15; i++){
            lpc_coeffs[i] *= -1;
        }
        ////////////////// TESTED //////////////////////



        //residuak_sig = filter(); filter our signal and obtain the residue signal
        float *residual_signal = filter(&lpc_coeffs[0], 14, n_frame, &sig_ham[0]);
        ////////////////// TESTED ///////////////////////


        // Estimate gain from residual_signal
        gain = gainEstimation(&residual_signal[0], n_frame);
        //////////////// TESTED ///////////////////////


        /////////////// TESTED BUT GAVE DIFFERENT FROM MATLAB ///////////////
        if (voiced_unvoiced_detection(pitch_ham, n_pitch) == 1){
            pitch_period = pitch_period_length(pitch_ham, n_pitch);
            printf("Voiced\t%d\t%d\n",pitch_period, i);
            //    //float *pitch_float = addPitch(pitch_period, prev_voiced, &prev_pitch_pos, i, n_frame);
            //    //overlapAdd(&pitch_float[0], &out_float[0], i, n_frame, n_step); 
            //    //free(pitch_float);
            //    prev_voiced = 1;
            //    printf("%d",prev_voiced);
        }
        else {
            printf("Unvoiced\n");
            //    //next_pitch_offset = 0;
            //    float *array = randNoise(n_frame);
            //    applyGain(&array[0], gain, n_frame);
            //    //filter(b_coeffs, a_coeffs, &array[0]);
            //    overlapAdd(&array[0], &out_float[0], i, n_frame, n_step);
            //    free(array);
            //    prev_voiced = 0; 
        }
        ////printf("Last in Array: %f\n", array[99]);
        ////free(array);


        ////int k;
        ////for (k = 0; k<480;k++)
        ////{
        ////    printf("%f\n", sig_ham[k]);
        ////}
        ////

        free(pitch_ham);
        free(sig_ham);
        free(pitch_segment); // free momey to avoid memlacage. Have to do in in foor loop
        free(sig_segment); // free momey to avoid memlacage. Have to do in in foor loop
    }

    sf_close(infile);
    return 0;
}
