
#include <stdio.h>
#include <stdlib.h>
#include <sndfile.h>
#include <math.h>
#include <string.h>
#include "hamming.h"

float *hamming_window(float frame[], int window_length){
    float alpha=0.54;
    float beta=1-alpha;
    
    float *windowed_frame=malloc(sizeof(float)*window_length);
    
    int i;
    for(i=0; i<window_length; i++){
        float temp_multiplier=alpha-beta*cos((2*3.14159*i)/(window_length-1));
        windowed_frame[i]=temp_multiplier*frame[i];
    }
    //for(i=0; i<window_length; i++){
    //    printf("%f \n", windowed_frame[i]);
    //}
    return windowed_frame;
}
