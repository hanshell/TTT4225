filename = 'files/original.wav';
Fs = 16000;
% 16000 * (20*10^-3)
N_frame = 320;
% 16000 * (30*10^-3)
N_ham = 480;
% 16000 * (50*10^-3)
N_pitch = 800;


% Create a hamming window of length N_ham
hamm = hamming( N_ham );

% Read audiofile. y is the data, Fs is the sampling rate
[ s, Fs ] = audioread( filename );

%soundsc( s(1:end,1), Fs )
O = s(14000:17400);

% Number of total iterations. The 1 comes from the first placing of the
% pitch window.
iter = floor((length(s) - N_pitch) / N_frame) + 1;

% Set start and stop-points for the frame. Cant start completely at the
% beginning since we have the window and pitch estimation segment should
% surround the frame symmetrically.
start = N_pitch/2 - N_frame/2;
stop = start + N_frame;

% To be able to multiply our signal with the window the arrays mst have the
% same length. Therefor we zero-pad in the front and in the end. ??? When
% doing this and then multiplying by the window, dont we loose a lot of
% what is good with a Hamming window? The part of the singnal that is mostly
% being compressed are just zero-padding.
padded_sig = zeros(N_ham,1);

% Array for the corresponding error-signal. or residual-signal.
err_sig = [];
%Array for the restored signal from the LP-coefficcients.
restored = [];
% array to store pitch placing
pitches = [];
% save info about the previous signal
prevVoiced = false;
prevPitchPos = start;
% the pitch-period in number of frames
pitchPeriod = 0;
for i = 1:iter;
    
    temp_sig = s(start : stop);
    % insert our signal to the middel of our zero-array
    padded_sig((N_ham - N_frame)/2 : (N_ham - N_frame)/2 + N_frame) = temp_sig;
    % coefficcients from the little frame of signal
    temp_coeffs = AR_coeffs(temp_sig, Fs);
    % error/residual-signal for the litte frame of signal
    temp_err = filter(temp_coeffs,1,temp_sig);
    % change where to start and stop the frame for the next iteration
    start = start + N_frame;
    stop = start + N_frame;
    % add our array
    err_sig = [err_sig; temp_err];
    % add to aray
    restored = [restored; filter(1,temp_coeffs, temp_err)];
    % Apply the window to our padded signal
    temp_sig_ham = padded_sig .* hamm;
    % remove padding and restore the signal to its real size
    unpadded_sig_ham = temp_sig_ham((N_ham - N_frame)/2 : (N_ham - N_frame)/2 + N_frame);
    % compute the fft to our unpadded ham signal
    %unpadded_sig_ham_fft = fft(unpadded_sig_ham_fft); 
    % have to use logarithmic scale in order to get funcitons that are easy
    % to extract info from
%     figure; hold on;
%     subplot(2,1,1)
%     plot(20*log10(abs(unpadded_sig_ham_fft)))
%     subplot(2,1,2)
%     plot(20*log10(abs(fft(temp_sig))))
%     waitforbuttonpress
    
    addPitch(prevVoiced, pitches, prevPitchPos, pitchPeriod, start, stop)
    gain = gain_estimation(temp_err);
end


%[ coeff, E ] = lpc( s, 14 );

% LP residual
%r = filter( coeff, 1, s);


%c = xcorr(O);
%R = [];

%for i = 1:length(c);
%    R = [R ; (c(i)/max(c))];
%end

