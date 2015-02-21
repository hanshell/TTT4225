filename = 'files/original.wav';
Fs = 16000;
% 16000 * (20*10^-3)
N_frame = 320;
% 16000 * (30*10^-3)
N_ham = 480;
% 16000 * (50*10^-3)
N_pitch = 800;

hamm = hamming( N_ham );

% Read audiofile. y is the data, Fs is the sampling rate
[ s, Fs ] = audioread( filename );
%s = s(1:end, 1);
%soundsc( s(1:end,1), Fs )
O = s(14000:17400);

% Number of total iterations. The 1 comes from the first placing of the
% pitch window.
iter = floor((length(s) - N_pitch) / N_frame) + 1;



%figure
%hold on
%plot( O )
%soundsc(O, Fs);
start = N_pitch/2 - N_frame/2;
stop = start + N_frame;

padded_sig = zeros(N_ham,1);

residue_sig = [];
restored = [];
for i = 1:iter;
    temp_sig = s(start : stop);
    padded_sig((N_ham - N_frame)/2 : (N_ham - N_frame)/2 + N_frame) = temp_sig;
    temp_coeffs = AR_coeffs(temp_sig, Fs);
    temp_residue = filter(temp_coeffs,1,temp_sig);
    start = start + N_frame;
    stop = start + N_frame; 
    residue_sig = [residue_sig; filter(temp_coeffs,1,temp_sig)];
    restored = [restored; filter(1,temp_coeffs, temp_residue)];
    temp_sig_ham = padded_sig .* hamm;
    unpadded_sig_ham = temp_sig_ham((N_ham - N_frame)/2 : (N_ham - N_frame)/2 + N_frame);
    
    unpadded_sig_ham1 = fft(unpadded_sig_ham);  
    figure; hold on;
    subplot(2,1,1)
    plot(20*log10(abs(unpadded_sig_ham1)))
    subplot(2,1,2)
    plot(20*log10(abs(fft(temp_sig))))
    waitforbuttonpress
end


%[ coeff, E ] = lpc( s, 14 );

% LP residual
%r = filter( coeff, 1, s);


%c = xcorr(O);
%R = [];

%for i = 1:length(c);
%    R = [R ; (c(i)/max(c))];
%end

