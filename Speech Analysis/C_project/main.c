/* 
 * File:   main.c
 * Author: hanshell
 *
 * Created on March 3, 2015, 11:29 AM
 */
#define FRAME_LENGTH 10

#include <stdio.h>
#include <stdlib.h>
#include <sndfile.h>
#include <math.h>

/*
 * 
 */
float *autocorrelation(float frame[], int frame_size);

int main(int argc, char** argv) {
    float frame[FRAME_LENGTH]={1, 3, 2, 4, 0.53, 2.3, 4.5, 1.4, 6.6, 7.8};
    float *auto_test=autocorrelation(frame, FRAME_LENGTH);
    int i;
    for(i=0; i<FRAME_LENGTH*2-1; i++){
        printf("*(auto_test + %d) : %f\n",  i, *(auto_test + i) );
    }
    return (EXIT_SUCCESS);
}
float *autocorrelation(float frame[], int frame_size){
    float *autocorrelation_array=malloc(sizeof(float)*FRAME_LENGTH);    //Allocate memory space
    float *symmetric_array=malloc(sizeof(float)*FRAME_LENGTH*2-1);      //Allocate memory space
    int i, j;
    for (i=0; i<frame_size; i++){
        float temp_sum=0;
        for(j=0; j<frame_size-i; j++){
            temp_sum+=(frame[j]*frame[j+i]);
        }
        autocorrelation_array[i]=temp_sum;
    }
    int k;
    for(k=0; k<FRAME_LENGTH; k++){
//        printf("%f \n", autocorrelation_array[k]);
    }
    int centering=FRAME_LENGTH-1;
    for (i=0; i<frame_size; i++){
        symmetric_array[centering-i]=autocorrelation_array[i];
        symmetric_array[centering+i]=autocorrelation_array[i];
    }
    return symmetric_array;
}
float *levinson_durbin_recursion(float frame[], int frame_size, int order){
    float *xcorr_frame=autocorrelation(frame, frame_size);

    int centering=(sizeof(xcorr_frame)/sizeof(xcorr_frame[0])+1)/2; //find center value peak
    
    float E=xcorr_frame[centering];

    int i;
    for(i=1; i<=order; i++){
        float k=xcorr_frame[centering+i];
        
        int j;
        for(j=1; j<i; j++){
            
        }
    }
}