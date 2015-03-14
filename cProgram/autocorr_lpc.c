

#include <stdio.h>
#include <stdlib.h>
#include <sndfile.h>
#include <math.h>
#include <string.h>
#include "autocorr_lpc.h"

float *autocorrelation(const float frame[], int frame_size) {
    float *autocorrelation_array = calloc(frame_size, sizeof (float)); //Allocate memory space
    int i, j;
    for (i = 0; i < frame_size; i++) {
        float temp_sum = 0;
        for (j = 0; j < frame_size - i; j++) {
            temp_sum += (frame[j] * frame[j + i]);
            //printf("%f\t%f\n", frame[j], frame[j+i]);
        }
        autocorrelation_array[i] = temp_sum;
        //printf("%f\n", temp_sum);
        
    }
    return autocorrelation_array;
}

float *levinson_durbin_recursion(const float frame[], int order, int frame_length) {
    float *xcorr_frame = autocorrelation(frame, frame_length);

    float E = xcorr_frame[0]; //Energy = autocorrelation in point n=0
    //printf("%f\n", E);
    float *a=calloc(order+1, sizeof(float));
    a[0] = 1;
    float b[order+1]; //={0};
        
    //Begin Levinson-Durbin recursion algorithm for finding LPC-coefficients
    int i, j;
    for(i=1; i<=order; i++){
        float k=xcorr_frame[+i];
        for(j=1; j<=i-1; j++){
            k=k-b[j]*xcorr_frame[i-j];
        }
        k=k/E;
        a[i]=k;
        for(j=1; j<=i-1; j++){
            a[j]=b[j]-(k*b[i-j]);
        }
        E=(1-(k*k))*E;
        for(j=1; j<=i; j++){
            b[j]=a[j];
        }
    }
    //End Levinson-Durbin recursion algorithm
    
    free(xcorr_frame);
    return a;
}