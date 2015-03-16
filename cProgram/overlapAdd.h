#include <stdlib.h>

void overlapAdd(float *segment, float *out_float, int i, int n_frame, int n_step);
void applyGain(float *segment, float gain, int n_frame);
void addExitationSegment(float *exitation_signal, int pitch_period, int framenr, int n_step, int n_frame, int classification, float gain, float *coeffs);
