

#include <stdio.h>
#include <stdlib.h>
#include <sndfile.h>
#include <math.h>
#include <string.h>
#include "autocorr_lpc.h"

float *autocorrelation(const float frame[], int frame_size) {
    float *autocorrelation_array = calloc(frame_size, sizeof (float)); //Allocate memory space
//    float *symmetric_array = calloc((frame_size * 2 - 1), sizeof(float)); //Allocate memory space
    int i, j;
    for (i = 0; i < frame_size; i++) {
        float temp_sum = 0;
        for (j = 0; j < frame_size - i; j++) {
            temp_sum += (frame[j] * frame[j + i]);
            printf("%f\t%f\n", frame[j], frame[j+i]);
        }
        autocorrelation_array[i] = temp_sum;
        printf("%f\n", temp_sum);
        
    }
/*    int centering = frame_size - 1;
    for (i = 0; i < frame_size; i++) {
        symmetric_array[centering - i] = autocorrelation_array[i];
        symmetric_array[centering + i] = autocorrelation_array[i];
    }
    free(autocorrelation_array);*/

    return autocorrelation_array;
}

float *levinson_durbin_recursion(const float frame[], int order, int frame_length) {
    float *xcorr_frame = autocorrelation(frame, frame_length);
//    int centering = (frame_length * 2 - 1) / 2;
//    printf("%d \n ", centering);

    float E = xcorr_frame[0];
    printf("%f\n", E);
    float a[order+1];
    a[0] = 1;
    float b[order+1]; //={0};
    
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
//            printf("a[j]: %f\n", a[j]);
            
        }
    }
    int k;
    for(k=0; k<=order; k++){
        printf("a[k]: %f\n", a[k]);
    }
    free(xcorr_frame);
    return a;
//    {1, 3, 2, 4, 0.53, 2.3, 4.5, 1.4, 6.6, 7.8, 3.2, 4.4, 6.5, 2.2, 23.1, 66.7};
}