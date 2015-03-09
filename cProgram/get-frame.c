#include "get-frame.h"

float *getFrame(int i, float *infile_float, int n_frame, int n_step)
{
    printf("Entered getFrame!\n");
    int j;
    float *segment = (float *)calloc(n_frame , sizeof(float));

    if (i == 0)
    {
        printf("if\n");
        for (j == 0; j < n_frame; j++)
        {
            segment[j] = infile_float[j];
            //printf("Infile_float: %f\n", infile_float[j]);
            //printf("Segment: %f\n", segment[j]);
        }
    }
    else
    {
        printf("else\n");
        for (j == 0; j < n_frame; j++)
        {
           segment[j] = infile_float[ i * n_frame + j ];
               //n_step +j ];
        }
    }
    return &segment[0];
}
