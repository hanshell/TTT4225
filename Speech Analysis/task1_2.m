filename = 'files/original.wav';

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



% Number of total iterations. The 1 comes from the first placing of the
% pitch window.
iter = floor((length(s) - N_pitch) / N_frame) + 1;

% Set start and stop-points for the frame. Cant start completely at the
% beginning since we have the window and pitch estimation segment should
% surround the frame symmetrically.
start_sig_frame = (N_pitch/2 - N_frame/2) + 1;
stop_sig_frame = N_pitch/2 + N_frame/2;

start_pitch_frame = 1;
stop_pitch_frame = 800;

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
pitches = zeros(1, length(s));
% save info about the previous signal
prevVoiced = 0;
prevPitchPos = start_sig_frame;
% the pitch-period in number of frames
pitchPeriod = 0;
ctr1 = 0;
ctr2 = 0;
synth = [];
for i = 1:iter;
    pitch_frame = s(start_pitch_frame : stop_pitch_frame);
    sig_frame = s(start_sig_frame : stop_sig_frame);
    
    % insert our signal to the middel of our zero-array
    padded_sig((N_ham - N_frame)/2 + 1 : (N_ham - N_frame)/2 + N_frame) = sig_frame;
    % Apply the window to our padded signal
    temp_sig_ham = padded_sig .* hamm;
    % remove padding and restore the signal to its real size
    unpadded_sig_ham = temp_sig_ham((N_ham - N_frame)/2 : (N_ham - N_frame)/2 + N_frame);
    % coefficcients from the little frame of signal
    temp_coeffs = AR_coeffs(unpadded_sig_ham, Fs);
    % error/residual-signal for the litte frame of signal
    temp_err = filter(temp_coeffs,1,unpadded_sig_ham);

    gain = gain_estimation(temp_err);    
   
    % check whether our signal is voiced or unvoiced
    if voiceclassification(pitch_frame) == 1;
        pitchPeriod = pitchperiod_detection(pitch_frame);
        [pitches(start_sig_frame : stop_sig_frame), prevPitchPos] = addPitch(prevVoiced, prevPitchPos, pitchPeriod, start_sig_frame, stop_sig_frame);
        pitches(start_sig_frame : stop_sig_frame) = pitches(start_sig_frame : stop_sig_frame)*gain;
        prevVoiced = 1;
        ctr1 = ctr1 + 1;
    else
        prevVoiced = 0;
        pitches(start_sig_frame : stop_sig_frame) = randn(1, length(sig_frame))*gain*0.1;
        ctr2 = ctr2 + 1;
    end
    
    synth = [synth, filter(1, temp_coeffs, pitches(start_sig_frame : stop_sig_frame))];
    
    
    % change where to start and stop the frame for the next iteration
    start_sig_frame = start_sig_frame + N_frame;
    stop_sig_frame = stop_sig_frame + N_frame;
    start_pitch_frame = start_pitch_frame + N_frame;
    stop_pitch_frame = stop_pitch_frame + N_frame;
    
    % add our array
    err_sig = [err_sig; temp_err];
    % add to aray
    restored = [restored; filter(1,temp_coeffs, temp_err)];


    % compute the fft to our unpadded ham signal
    %unpadded_sig_ham_fft = fft(unpadded_sig_ham_fft); 
    
    
    
    %waitforbuttonpress
end
ctr1
ctr2


