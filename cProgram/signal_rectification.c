#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

float *frame_rectification(float  frame[], int frame_size){
    float *rectified_frame=calloc(frame_size, sizeof(float));
    int i;
    for(i=0; i<frame_size; i++){
        rectified_frame[i]=abs(frame[i]);
    }
}
