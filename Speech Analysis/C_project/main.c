/* 
 * File:   main.c
 * Author: hanshell
 *
 * Created on March 3, 2015, 11:29 AM
 */
#include <stdio.h>
#include <stdlib.h>
#include <sndfile.h>
#include <string.h>
#include "autocorr_lpc.h"
#include "hamming.h"
/*
 * 
 */
int main(int argc, char** argv) {
    float frame[FRAME_LENGTH]={1, 3, 2, 4, 0.53, 2.3, 4.5, 1.4, 6.6, 7.8, 3.2, 4.4, 6.5, 2.2, 23.1, 66.7};
    printf(" Frame size: %f\n", sizeof(frame)/sizeof(frame[0]));
//    float *auto_test=autocorrelation(frame, FRAME_LENGTH);
    float *hamming_test=hamming_window(frame, 16);
    int i;
    for(i=0; i<FRAME_LENGTH*2-1; i++){
//        printf("*(auto_test + %d) : %f\n",  i, *(auto_test + i) );
    }
//    float *lp=levinson_durbin_recursion(frame, PREDICTION_ORDER);
    
    
//    free(auto_test);
    free(hamming_test);
    
    
    return (EXIT_SUCCESS);
}