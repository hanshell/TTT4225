#include <stdlib.h>

void overlapAdd(float *segment, float *out_float, int i, int n_frame, int n_step);
void applyGain(float *segment, float gain, int n_frame);
float *addPitch(int pitch_period, int prev_voiced, int prev_pitch_pos, int i, int n_frame);
