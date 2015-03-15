
#include <stdio.h>
#include <stdlib.h>
#include <sndfile.h>
#include <math.h>
#include <string.h>

#include "autocorr_lpc.h"
#include "voice_classification.h"

/*
 * Finds amount of zero crossings of the autocorrelation of a frame
 */
int find_zero_crossings(float frame[], int frame_length){
    int i;
    int zero_crossing_count=0;
    for(i=0; i<frame_length-1; i++){
        float temp_1=frame[i];
        float temp_2=frame[i+1];
        
        if((temp_1>0 && temp_2<0) ||(temp_1<0 && temp_2>0)){
            zero_crossing_count++;

        }
    }
    return zero_crossing_count;
}
/*
 * determines a segment to be voiced or unvoiced based on 
*/
int voiced_unvoiced_detection(float frame[], int frame_length){
    float *xcorr_frame=autocorrelation(frame, frame_length);
    int zero_crossing_threshold=40; //zero crossing threshold. Unvoiced sounds have high zero crossing rate. Opposite for voiced.
    
    int zero_crossings=find_zero_crossings(xcorr_frame, frame_length);
    
    free(xcorr_frame);
    
    if(zero_crossings>zero_crossing_threshold){
        return 0;
    }
    else{
        int period=pitch_period_length(frame, frame_length);
        if(period<32 || period>320){
            return 0;
        }
        else{
            return 1;
        }
    }
    
/*    if(zero_crossings<zero_crossing_threshold) return 1;
*    else return 0;
*/    
}
/*
 This function uses zero crossings to find the pitch period by calculating the mean distance
 * between crossings, and then multiplying by two (because there are usually two zero crossings
 * for each pitch period. NB: this function should only be used for frames that are known to be
 * voiced
 */
int pitch_period_length(float frame[], int frame_length){
    float *xcorr_frame=autocorrelation(frame, frame_length);
    
    int zerocrossings=find_zero_crossings(xcorr_frame, frame_length); //total number of zero crossings in frame
    int zero_crossing_distances[zerocrossings]; //Array to contain distance between each zero crossing
    
    int counter=0;
    int zero_crossing_counter=0;
    int i;    
    for(i=0; i<frame_length; i++){

        float temp_1=xcorr_frame[i];
        float temp_2=xcorr_frame[i+1];
        
        if((temp_1>0 && temp_2<0)||(temp_1<0 && temp_2>0)){
            zero_crossing_distances[zero_crossing_counter]=counter; //add distance to array each time a zero crossing occurs
            counter=0; //reset counter
            zero_crossing_counter++;
        }
        else{
            counter++; //increment counter if zero crossing does not occur
        }
    }
    int zerocrossing_distance_sum=0;
    for(i=0; i<zerocrossings; i++){
        zerocrossing_distance_sum+=zero_crossing_distances[i];
    }
    int pitchperiod=(zerocrossing_distance_sum/zerocrossings)*2;
    free(xcorr_frame);
    return pitchperiod;
}

