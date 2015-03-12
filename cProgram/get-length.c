int getLength(int tot_frames, int n_frame, int n_step, int *n_iter)
{
int n_pad;
int step_part = tot_frames - n_frame;
int complete_steps = step_part / n_step; // add one for getting over tot_frame
n_pad = n_frame + (complete_steps + 1) * n_step - tot_frames;
*n_iter = complete_steps + 2; // add 1 for the ekstra step and one for the n_frames removed in the beginning
return n_pad;
}
