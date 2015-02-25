filename = 'files/original.wav'; % name/location of audiofile to be read
[s, Fs] = audioread(filename);

% Some constants
n_frame = 480; % lenght of frame we multiply with our hamming window
n_step = 320; % how far we each step is

residual = getResidual(s, n_frame, n_step);





