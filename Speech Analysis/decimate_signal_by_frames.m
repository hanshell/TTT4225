function [ decimated_signal ] = decimate_signal_by_frames( signal, frame_length, decimation_factor )
%UNTITLED Summary of this function goes here
%   Detailed explanation goes here

padding_length=ceil(length(signal)/frame_length)*frame_length-length(signal)+1;
zero_paddded_vector=zeros(padding_length, 1);
padded_signal=[signal ; zero_paddded_vector];

signal_decimated=[];

for i=1:length(padded_signal)/frame_length;
   temp_decimate=decimate(padded_signal(frame_length*(i-1)+1:frame_length*i+1), decimation_factor);
   signal_decimated=[signal_decimated;temp_decimate];
end

decimated_signal=signal_decimated;

end

