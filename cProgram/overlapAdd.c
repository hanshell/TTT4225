#include <stdlib.h>
#include <stdio.h>

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
    for (i = 0; i < n_frame; i++) {
        printf("%f\n", segment[i]);
    }

}

float *addPitch(int pitch_period, int prev_voiced, int *prev_pitch_pos, int i, int n_frame) {

    offset = *next_pitch_offset;
    int j;
    float *segment = NULL;
    segment = (float *)calloc(n_frame, sizeof(float));


    if (prev_voiced == 1) {
        for (j = pitch_period - offset; j < n_frame; j += pitch_period) {
            segment[j] = 1;            
            *prev_pitch_pos = 
        }
    }
    else {
        for (j = 0; j < n_frame; j += pitch_period){
            segment[j] = 1; 
            *prev_pitch_pos = i*n_f;
        } 
    } 
}
