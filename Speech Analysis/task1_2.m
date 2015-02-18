filename = 'files/original.wav';
Fs = 16000;
% 16000 * (20*10^-3)
N_frame = 320;
% 16000 * (30*10^-3)
N_ham = 480;
%16000 * (50*10^-3)
N_pitch = 800;

ham = hamming( N_ham );

% Read audiofile. y is the data, Fs is the sampling rate
[ s, Fs ] = audioread( filename );
s = s(1:end, 1);
%soundsc( s(1:end,1), Fs )
O = s(14000:17400);
%length of extracted signal. One letter pronounced
signal_len = 17400 - 14000;

number_of_win = floor(3400 / N_ham);

figure
hold on
subplot(2,1,1)
plot( O )
soundsc(O, Fs);

[ coeff, E ] = lpc( s, 14 );

% LP residual
r = filter( coeff, 1, s);



