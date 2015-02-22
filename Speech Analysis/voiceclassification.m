function [ classification ] = voiceclassification( audio_segment )

% Analysis a sound signal segment and determines whether it is voiced or
% unvoiced based on a set threshold value
%   
Fs=16000;

xcorr_audio_segment=xcorr(audio_segment);

ratio=max(xcorr_audio_segment(800+Fs/500:800+Fs/50))/max(xcorr_audio_segment(775:825));

threshold=0.5;

detection=-1; % 0 if voiced, 1 if unvoiced;

if ratio>=threshold
    detection=1;
else
    detection=0;
end

classification=detection;


end

