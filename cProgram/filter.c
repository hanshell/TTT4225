#include <stdlib.h>
float *filter(float coeffs[], int order, int n_frame, float*segment) {
    /* The order specified in the levinson durbin recursion returns
     * order + 1 coefficients
     */
    order = order + 1;

    /*Iniitialize output -> the array storing the complete
     * filtered signal
     * and mem -> the array storing the previous values from
     * the input signal that is used in this filter
     * */
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
        }
        nt++;
    }
    return &output[0];
}
