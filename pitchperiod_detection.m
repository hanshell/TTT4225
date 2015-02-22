function [ pitchperiod ] = pitchperiod_detection( signalsegment )
% Detects period of a voiced speech segment based on autocorrelation peaks
%   
Fs=16000; % Sampling rate

[period, value]=max(signalsegment(Fs/500:Fs/50));

pitchperiod=period;

end

