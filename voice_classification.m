% Run record_audio.m before running this script!

myRecording_sample=myRecording(1:800);
xcorr_myRecording_sample=xcorr(myRecording_sample);
xcorr_medianfiltered=medfilt1(xcorr_myRecording_sample, 10);
threshold=0.2;

detection=-1; %0 if voiced, 1 if unvoiced;

peaks=findpeaks(xcorr_medianfiltered);

ratio=mean(peaks)/max(peaks);

if ratio>threshold
    detection=0;
else
    detection=1;
end



ratio=mean(peaks)/max(peaks);
sound(myRecording);
x = diff(sign(myRecording_sample));



%plot(abs(fft(xcorr_myRecording_sample)));