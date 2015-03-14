#include <math.h>
#include <stdlib.h>
#include <stdio.h>

#include "gain-estimation.h"


float gainEstimation(float *signal, int n_signal)
{
    int i;

    float power = 0;


    for (i = 0; i < n_signal; i++)
    {

       power = power + pow(signal[i], 2);
       //printf("%f\n", power);
    }
    power = power / n_signal;
    
    return sqrt(power);
}
