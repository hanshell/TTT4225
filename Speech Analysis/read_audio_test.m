% % Creates a AudioRecorder object
% mic = dsp.AudioRecorder;
% mic.SampleRate = 16000;
% % Create empty vector to store recorded data
% y = [];
% 
% % Collect 50 steps of voice from microphone and add to y
% for i = 1:10;
%     y = [y; step(mic)];
% end
% 
% soundsc(y,Fs)


%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%

% Record your voice for 5 seconds.
% Setting samplerate to Fs, number of bits pr sample to 8 and number of
% channels to 1
recObj = audiorecorder(Fs, 8, 1);
disp('Start speaking.')
% Records to recObj for 2 seconds
recordblocking(recObj, 2);
disp('End of Recording.');

% Store data in double-precision array.
myRecording = getaudiodata(recObj);
soundsc(myRecording, Fs);
% Plot the waveform.
plot(myRecording);

%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%