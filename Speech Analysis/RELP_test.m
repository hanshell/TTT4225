file_anvendt='files/anvsb1.wav';


% 16000 * (20*10^-3)
N_frame = 320;
% 16000 * (30*10^-3)
N_ham = 480;
% 16000 * (50*10^-3)

% 16000 * (50*10^-3)
N_pitch = 800;

start_sig_frame = (N_pitch/2 - N_ham/2) + 1;
stop_sig_frame = N_pitch/2 + N_ham/2;

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
[ s, Fs ] = audioread( file_anvendt );

number_of_iterations = floor((length(s) - N_pitch) / N_frame) + 1;

error_signal=[];
error_decimate=[];
error_interpolate=[];

restored_signal=[];

for i = 1:number_of_iterations;
    sig_frame = s(start_sig_frame : stop_sig_frame);
    
    % Apply the window to our padded signal
    sig_ham = sig_frame .* hamm;
    % coefficcients from the little frame of signal
    coeffs = lpc(sig_ham, 14);
    
    % error/residual-signal for the litte frame of signal
    temp_err = filter(coeffs,1,sig_ham);
    temp_error_decimate=decimate(temp_err, 4, 'FIR');
    temp_error_interpolate=interp(temp_error_decimate, 4);
    
    start_sig_frame = start_sig_frame + N_frame;
    stop_sig_frame = stop_sig_frame + N_frame;
    start_pitch_frame = start_pitch_frame + N_frame;
    stop_pitch_frame = stop_pitch_frame + N_frame;

    
    error_signal=[error_signal; temp_err];
    error_decimate=[error_decimate; temp_error_decimate];
    error_interpolate=[error_interpolate; temp_error_interpolate];
    temp_restored=filter(1, coeffs, temp_error_interpolate);
    restored_signal=[restored_signal; temp_restored];
    
end

figure(1);
subplot(3,1,1);
plot(error_signal);
subplot(3,1,2);
plot(error_decimate);
subplot(3,1,3);
plot(error_interpolate);
sound(error_signal, Fs);