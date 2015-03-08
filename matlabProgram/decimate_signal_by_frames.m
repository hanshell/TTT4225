function [ decimated_signal, total_signal ] = decimate_signal_by_frames( signal, frame_length, decimation_factor )
%UNTITLED Summary of this function goes here
%   Function returns each decimated frame as a vector in a 2d-array

padding_length=ceil(length(signal)/frame_length)*frame_length-length(signal);
zero_paddded_vector=zeros(padding_length, 1);
padded_signal=[signal ; zero_paddded_vector];

signal_decimated=zeros(length(padded_signal)/frame_length, frame_length/decimation_factor+1);
total_signal=[];
for i=1:length(padded_signal)/frame_length-1;
   temp_decimate=decimate(padded_signal(frame_length*(i-1)+1:frame_length*i+1), decimation_factor);
   signal_decimated(i, :) = temp_decimate;
end
k=0;
for i=1:length(signal_decimated);
    for j=1:length(signal_decimated(i, :));
        total_signal=[total_signal ; signal_decimated(i, j)]; 
%        length(signal_decimated)
%        length(signal_decimated(i))
%        total_signal
%        k=k+1
    end
end

decimated_signal=signal_decimated;

end