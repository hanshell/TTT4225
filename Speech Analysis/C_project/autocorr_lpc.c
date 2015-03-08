

#include <stdio.h>
#include <stdlib.h>
#include <sndfile.h>
#include <math.h>
#include <string.h>
#include "autocorr_lpc.h"

float *autocorrelation(float frame[], int frame_size) {
    float *autocorrelation_array = malloc(sizeof (float)*FRAME_LENGTH); //Allocate memory space
    float *symmetric_array = malloc(sizeof (float)*FRAME_LENGTH * 2 - 1); //Allocate memory space
    int i, j;
    for (i = 0; i < frame_size; i++) {
        float temp_sum = 0;
        for (j = 0; j < frame_size - i; j++) {
            temp_sum += (frame[j] * frame[j + i]);
        }
        autocorrelation_array[i] = temp_sum;
    }
    int k;
    for (k = 0; k < FRAME_LENGTH; k++) {
        //        printf("%f \n", autocorrelation_array[k]);
    }
    int centering = FRAME_LENGTH - 1;
    for (i = 0; i < frame_size; i++) {
        symmetric_array[centering - i] = autocorrelation_array[i];
        symmetric_array[centering + i] = autocorrelation_array[i];
    }
    return symmetric_array;
}

float *levinson_durbin_recursion(float frame[], int order) {
    float *xcorr_frame = autocorrelation(frame, FRAME_LENGTH);

    int i1;
    for (i1 = 0; i1 < FRAME_LENGTH * 2 - 1; i1++) {
        printf("*(xcorr_frame + %d) : %f\n", i1, *(xcorr_frame + i1));
    }
    int centering = (FRAME_LENGTH * 2 - 1) / 2;
    printf("%d \n ", centering);

    float E = xcorr_frame[centering];
    float a[order]; //={0};
    a[0] = 1;
    float b[order]; //={0};

    float lpc[order];
    lpc[0] = 1;

    int i, j;
    for (i = 0; i < order; i++) {
        float k = xcorr_frame[(i + 1) + centering];
        for (j = 0; j < i - 1; j++) {
            k = k - b[j] * xcorr_frame[(i + 1 + centering)-(j + 1 + centering)];
        }
        k = k / E;
        a[i] = k;
        //        printf("%f \n", a[i]);

        for (j = 0; j < i; j++) {
            a[j] = b[j]-(k * b[i - j]);
            //            printf("b[j]: %f \t a[j]: %f \n", b[j], a[j]);

        }
        E = (1 - (k * k)) * E;
        for (j = 0; j <= i; j++) {
            b[j] = a[j];
            //            printf("b[j]: %f \n", b[j]);
        }
    }
    for (j = 0; j <= i; j++) {
        b[j] = a[j];
        printf("a[j] first: %f \n", a[j]);
    }
    for (i1 = 0; i1 < order; i1++) {
        printf("Prediction coefficients: %f\n", b[j]);
    }

    return a;
}