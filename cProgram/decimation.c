#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

float *downsample_frame(float frame[], int frame_size, int downsample_factor){
    float *downsampled_frame=calloc(frame_size/4, sizeof(float));
    
    int i;
    for(i=0; i<frame_size; i=i+downsample_factor){
        downsampled_frame[i/downsample_factor]=frame[i];
        printf("%f\n", frame[i]);
    }
    return downsampled_frame;
}