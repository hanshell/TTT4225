#include <stdlib.h>
#include <stdio.h>

#include "Randnoise.h"
#include "filter.h"


void overlapAdd(float *segment, float *out_float, int i, int n_frame, int n_step) {
    int j;
    for (j = 0; j < n_frame; j++) {
        if (i == 0) {
            out_float[j] = segment[j];
        }
        else {
            out_float[i*n_step + j] += segment[j];

        }
    }
}

void applyGain(float *segment, float gain, int n_frame) {
    int i;

    for (i = 0; i < n_frame; i++) {
        segment[i] *= gain; 
    }

}

void addExitationSegment(float *exitation_signal, int pitch_period, int framenr, int n_step, int n_frame, int classification, float gain, float *coeffs) {
    int j;

    if (classification == 1) {
        float *pitches = (float *)calloc(n_frame, sizeof(float));
        for (j = 0; j < n_frame; j += pitch_period) {
            pitches[j] = 1;
        }
        float *filtered = ARfilter(&coeffs[0], 14, n_frame, &pitches[0], gain);
        overlapAdd(&filtered[0], &exitation_signal[0], framenr, n_frame, n_step);
        free(filtered);
        free(pitches);
    } 
    else {
        gain *= 0.1;
        float *whitenoise = randNoise(n_frame);
        float *filtered = ARfilter(&coeffs[0], 14, n_frame, &whitenoise[0], gain);
        overlapAdd(&filtered[0], &exitation_signal[0], framenr, n_frame, n_step);
        free(filtered);
        free(whitenoise);
    }





    //if (classification == 1) {
    //    int length = framenr*n_step + n_frame - *next_position;

    //    float *ex_seg;
    //    ex_seg = (float *)calloc(length, sizeof(float));

    //    for (j = 0; j < length; j += pitch_period) {
    //        ex_seg[j] = 1; 
    //    }

    //    for (j = 0; j < length; j++){
    //        exitation_signal[*next_position + j] = ex_seg[j];
    //        //exitation_signal[j] = 1;
    //    } 
    //    *next_position = j - pitch_period + 1;
    //    free(ex_seg);
    //}
    //else {
    //    float *whitenoise = randNoise(n_frame);
    //    for (j = 0; j < n_frame; j++) {
    //        exitation_signal[framenr*n_step + j] = whitenoise[j];
    //    }
    //    free(whitenoise);
    //}





    //float *segment;
    //segment = (float *)calloc(480, sizeof(float));

    //if (prev_voiced == 1) {
    //    for (j = pitch_period - offset; j < n_frame; j += pitch_period) {
    //        segment[j] = 1;            
    //    }

    //}
    //else {
    //    for (j = last_position; j < framenr*n_step + n_frame; j += pitch_period){
    //        exitation_signal[j] = 1;
    //        //            segment[j] = 1; 
    //    } 
    //    *last_position = j - pitch_period;
    //} 
}
