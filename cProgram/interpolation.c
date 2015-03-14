#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

#include "interpolation.h"

float *upsample_frame(float frame[], int frame_size, int upsampling_factor){
    float *upsampled_frame=calloc(frame_size*upsampling_factor, sizeof(float));
    
    int i;
    for(i=0; i<frame_size*upsampling_factor; i++){
        upsampled_frame[i*upsampling_factor]=frame[i];
    }
    return upsampled_frame;
}