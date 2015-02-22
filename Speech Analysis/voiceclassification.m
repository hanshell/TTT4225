function [ classification ] = voiceclassification( audio_segment )

% Analysis a sound signal segment and determines whether it is voiced or
% unvoiced based on a set threshold value
%   
xcorr_audio_segment=xcorr(audio_segment);
xcorr_medianfiltered=medfilt1(xcorr_audio_segment, 10);
threshold=0.27;

detection=-1; % 0 if voiced, 1 if unvoiced;

peaks=findpeaks(xcorr_medianfiltered);

ratio=mean(peaks)/max(peaks);

if ratio>=threshold
    detection=1;
else
    detection=0;
end

classification=detection;


end

