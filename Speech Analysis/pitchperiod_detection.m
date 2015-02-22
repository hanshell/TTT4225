function [ pitchperiod ] = pitchperiod_detection( signalsegment )
% Detects period of a voiced speech segment based on autocorrelation peaks
%   
Fs=16000; % Sampling rate

xcorr_signalsegment=xcorr(signalsegment);

plot(xcorr_signalsegment);

[value, period]=max(xcorr_signalsegment(800+Fs/500:800+Fs/50));

pitchperiod=period+Fs/500; % Add offset due to maximum autocorrelation value starting at 800

end

