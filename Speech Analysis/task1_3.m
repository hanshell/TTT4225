filename = 'files/original.wav';
[s, Fs] = audioread(filename);

% Some constants
n_frame = 480; % lenght of frame we multiply with our hamming window
n_step = 320; % how far we each step is
n_sig = length(s);
n_iter = ceil((n_sig - n_frame) / n_step) + 1; 
padding = zeros((n_frame + n_step * n_iter -1) - n_sig - 1 ,1); % the padding we need to fill the n_iter'th signal
s = [s ; padding];
n_sig = length(s); % length of the signal

res = zeros(n_sig, 1); 

all_coeffs=zeros(n_iter, 15);

for i = 1 : n_iter;
    frame = getFrame(i, s, n_frame, n_step);
    frame_ham = frame .* hamming(n_frame);
    
    coeffs = lpc(frame_ham, 14);
    
    all_coeffs(i, :)=coeffs;
    
    frame_residual = filter(coeffs, 1, frame_ham);

    if i == 1;
        res(1 : n_frame) = frame_residual;
        
    else
        res( ((i-1)*n_step) + 1 : (n_frame + (i-2)*n_step) ) = res( ((i-1)*n_step) + 1 : (n_frame + (i-2)*n_step) ) + frame_residual(1: (n_frame - n_step));
        res( (n_frame + (i-2)*n_step) +1 : i*n_step+(n_frame - n_step) ) = frame_residual(n_frame - n_step + 1 : end);
    end
    
    


%res = res(1: end - length(padding));

residual_decimated = decimate(res(1 : n_frame), 4); % 1/R times
plot(residual_decimated)
residual_interpolated = upsample(residual_decimated, 4);
% [H,w] = freqz(residual_interpolated);
aA = fir1(10, 2000/(Fs/2), 'low'); % gives a filter that has cutoff freq 0.25

residual_interpolated_low = filter(aA,1,residual_interpolated);
% [HH,ww] = freqz(residual_interpolated_low);
% figure
% subplot(2,1,1)
% plot(w/pi,abs(H))
% subplot(2,1,2)
% plot(ww/pi,abs(HH))

recificated_residual = abs(residual_interpolated_low);

[H,w] = freqz(recificated_residual);
rp = 3;           % Passband ripple
rs = 40;          % Stopband ripple
fs = 16000;        % Sampling frequency
f = [5000 6000];    % Cutoff frequencies
aA = [1 0];        % Desired amplitudes
dev = [(10^(rp/20)-1)/(10^(rp/20)+1)  10^(-rs/20)];
[n,fo,ao,w] = firpmord(f,aA,dev,fs);
b = firpm(n,fo,ao,w);
% freqz(b,1,1024,fs)
% title('Lowpass Filter Designed to Specifications')
%B = firpmord();

rec_res_estimate = filter(b,1,recificated_residual);
[H,w] = freqz(rec_res_estimate);
%plot(w/pi,20*log10(abs(H)))

end

