#include <stdlib.h>
#include "get-frame.h"
float *getFrame(int i, float *infile_float, int n_frame, int n_step)
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
segment[j] = infile_float[j];
//printf("Infile_float: %f\n", infile_float[j]);
//printf("Segment: %f\n", segment[j]);
}
}
else
{
for (j = 0; j < n_frame; j++)
{
segment[j] = infile_float[ i * n_step + j ];
//n_step +j ];
}
}
return &segment[0];
}
