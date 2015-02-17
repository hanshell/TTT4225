file_baba='Speech Analysis/files/baba1.wav';
file_anvendt='Speech Analysis/files/anvsb1.wav';

[y1, Fs1]=audioread(file_baba); % Bæ bæ lille lam soundfile
[y2, Fs2]=audioread(file_anvendt); % "Anvendt signalbehandling er kult" soundfile

voiced_sound=74000:83000; % Samples of the first sound file with two sequential vowels (a and e)
unvoiced_sound=46000:48000; % Samples of the second osund file with an unvoiced sound (f)

figure(1)

subplot(4,1,1);
plot(y1);
xlabel('Samples');
ylabel('Sound amplitude');
title('First sound file');

subplot(4,1,2);
plot(y2);
xlabel('Samples');
ylabel('Sound amplitude');
title('Second sound file');

subplot(4,1,3);
plot(y1(74000:83000));
xlabel('Samples');
ylabel('Sound amplitude');
title('Voiced sound (sequential vocals o and e');

xlabel('Samples');
title('Unvoiced sound (f)');

sound(y1(voiced_sound), Fs1);
subplot(4,1,4);
plot(y2(46000:48000));
pause(1);
ylabel('Sound amplitude');
sound(y2(unvoiced_sound), Fs2);
pause(1);
%% 
% As shown by the graph, the voiced sounds have a periodicity over time with respect to the sound amplitude, while the
% unvoiced sounds resemble white noise. 

%y3=y1(voiced_sound);
y3=y1(10000:100000);

[lpc_oe, g]=lpc(y3, 14);

oe_output=filter(1, lpc_oe, y3);

sound(y3, Fs1);
pause(7);
sound(oe_output./20, Fs1);

figure
subplot(3,1,1),
plot(y3);
subplot(3,1,2);
plot(oe_output);
subplot(3,1,3);
plot((oe_output)-y3);