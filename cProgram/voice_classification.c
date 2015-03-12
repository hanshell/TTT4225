
#include <stdio.h>
#include <stdlib.h>
#include <sndfile.h>
#include <math.h>
#include <string.h>

int find_zero_crossings(const float frame[], int frame_length){
    int i;
    int zero_crossing_count=0;
    for(i=0; i<frame_length-1; i++){
        int temp_1=frame[i];
        int temp_2=frame[i+1];
        
        if((temp_1>0 && temp_2<0)||(temp_1<0 && temp_2>0)){
            zero_crossing_count++;
        }
    }
    return zero_crossing_count;
}
int voiced_unvoiced_detection(const float frame[], int frame_length){
    int zero_crossing_threshold=40; //zero crossing threshold. Unvoiced sounds have high zero crossing rate. Opposite for voiced.
    
    if(find_zero_crossings(frame, frame_length)<zero_crossing_threshold) return 1;
    else return 0;
    
}