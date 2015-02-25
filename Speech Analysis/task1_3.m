filename = 'files/original.wav';
[s, Fs] = audioread(filename);

% Some constants
n_frame = 480; % lenght of frame we multiply with our hamming window
n_step = 320; % how far we each step is
n_iter = ceil((n_sig - n_frame) / n_step) + 1; 
n_sig = length(s);
padding = zeros((n_frame + n_step * n_iter -1) - n_sig - 1 ,1); % the padding we need to fill the n_iter'th signal
s = [s ; padding];
n_sig = length(s); % length of the signal

res = zeros(n_sig, 1); 

for i = 1 : n_iter;
    frame = getFrame(i, s, n_frame, n_step);
    frame_ham = frame .* hamming(n_frame);
    
    coeffs = lpc(frame_ham, 14);
    
    frame_residual = filter(coeffs, 1, frame_ham);

    if i == 1;
        res(1 : n_frame) = frame_residual;
        
    else
        res( ((i-1)*n_step) + 1 : (n_frame + (i-2)*n_step) ) = res( ((i-1)*n_step) + 1 : (n_frame + (i-2)*n_step) ) + frame_residual(1: (n_frame - n_step));
        res( (n_frame + (i-2)*n_step) +1 : i*n_step+(n_frame - n_step) ) = frame_residual(n_frame - n_step + 1 : end);
    end
    
    
end

res = res(1: end - length(padding));