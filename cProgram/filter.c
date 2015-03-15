#include <stdlib.h>
float *filter(float coeffs[], int order, int n_frame, float*segment) {
    order = order + 1;
    float *output, *mem;
    output = (float *)calloc(n_frame, sizeof(float));
    mem = (float *)calloc(order, sizeof(float));

    printf("FØRSTE fra seg: %f\n", segment[0]);
    
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
