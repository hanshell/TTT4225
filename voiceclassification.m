function [ classification ] = voiceclassification( audio_segment )

% Analysis a sound signal segment and determines whether it is voiced or
% unvoiced based on a set threshold value
%   
myRecording_sample=myRecording(1:320);
xcorr_myRecording_sample=xcorr(myRecording_sample);
xcorr_medianfiltered=medfilt1(xcorr_myRecording_sample, 10);
threshold=0.2;

detection=-1; % 0 if voiced, 1 if unvoiced;

peaks=findpeaks(xcorr_medianfiltered);

ratio=mean(peaks)/max(peaks);

if ratio>=threshold
    detection=0;
else
    detection=1;
end

classification=detection;


end

