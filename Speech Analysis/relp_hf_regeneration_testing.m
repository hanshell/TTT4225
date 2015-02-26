Fs=16000;
decimated_signal=decimate_signal_by_frames(res, 320, 4); %% Decimates and lwpass filters each segment
y=[];
for i=1:length(decimated_signal);
   y=[y ; decimated_signal(i, :)];
end

decimated_signal_transpose=decimated_signal';


z=reshape(decimated_signal, length(decimated_signal)*length(decimated_signal(1, :)), 1);