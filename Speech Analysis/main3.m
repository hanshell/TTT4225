filename = 'files/original.wav'; % name/location of audiofile to be read
[s, Fs] = audioread(filename);

% Some constants
n_frame = 480; % lenght of frame we multiply with our hamming window
n_step = 320; % how far we each step is

% the residual signal is calculated in our function and returned to the array.
residual = getResidual(s, n_frame, n_step); 
lp_residual = lowpassFilter(residual);
[H,w] = freqz(residual);
[H2,w2] = freqz(lp_residual);
figure
subplot(2,1,1)
plot(w/pi,abs(H))
subplot(2,1,2)
plot(w2/pi,abs(H2))

