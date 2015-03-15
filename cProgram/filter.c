#include <stdlib.h>
#include <stdio.h>
float *MAfilter(float coeffs[], int order, int n_frame, float *segment, float gain) {

    /* The order specified in the levinson durbin recursion returns
     * order + 1 coefficients
     */
    order = order + 1;
    float *output, *mem;
    output = (float *)calloc(n_frame, sizeof(float));
    mem = (float *)calloc(order, sizeof(float));

    int n, i, Nuse, nt = 0;

    for (n = 0; n < n_frame; n++) {
        mem[nt%order] = segment[n];
        Nuse = order;
        if(nt < order){
            Nuse = nt+1;
        }
        for (i = 0; i < Nuse; i++){
            output[n] += coeffs[i]*mem[((nt-i)%order)]; 
            //output[n] *= gain;
        }
        nt++;
    }
    return &output[0];
}

float *ARfilter(float coeffs[], int order, int n_frame, float *segment, float gain) {
    order = order + 1;
    float *output, *mem;

    output = (float *)calloc(n_frame, sizeof(float));
    mem = (float *)calloc(order, sizeof(float));

    int n, i, Nuse, nt = 0;

    for (n = 0; n < n_frame; n++) {
        output[n] = segment[n];
        Nuse = order;
        if(nt < order){
            Nuse = nt;
        }
        for (i = 0; i < Nuse; i++){
            output[n] += coeffs[i]*mem[((nt-i-1)%order)]; 
            //output[n] *= gain;
        }
        mem[nt%order] = output[n];
        nt++;
    }


    return &output[0];

}

