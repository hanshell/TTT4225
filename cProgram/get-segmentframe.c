#include <stdlib.h>
#include "get-segmentframe.h"

float *getSegmentFrame(int i, float *infile_float, int n_frame, int n_step, int offset)
{
    //printf("Entered getFrame!\n");
    //printf("INFILE FLOAT %f\n",infile_float[0]);
    int j;
    float *segment = NULL;
    segment = (float *)calloc(n_frame , sizeof(float));


    if (i == 0)
    {
        for (j = 0; j < n_frame; j++)
        {
            //printf("%f\n",infile_float[j]);
            segment[j] = infile_float[j + offset];
            //printf("Infile_float: %f\n", infile_float[j]);
            //printf("Segment: %f\n", segment[j]);
        }


    }
    else
    {
        for (j = 0; j < n_frame; j++)
        {
            segment[j] = infile_float[ i * n_step + j + offset ];
            //n_step +j ];
        }
    }
    return &segment[0];
}
