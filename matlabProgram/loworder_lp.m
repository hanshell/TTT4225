function [ lowlp_filtered, total_signal ] = loworder_lp( rectified_signal )
%UNTITLED5 Summary of this function goes here
%   Detailed explanation goes here

signal_lowlpfiltered=zeros(length(rectified_signal(:, 1)), length(rectified_signal));


for i=1:length(rectified_signal(:, 1));
    temp_frame=rectified_signal(i, :);
    temp_coeff=lpc(temp_frame, 4);
    
    temp_coeff
    
    temp_lpfiltered=filter(temp_coeff, 1, temp_frame);
    
    signal_lowlpfiltered(i, :)=temp_lpfiltered;
end

total_signal=[];

for i=1:length(signal_lowlpfiltered(:, 1));
    for j=1:length(signal_lowlpfiltered(i, :));
        total_signal=[total_signal ; signal_lowlpfiltered(i, j)];
    end
end

lowlp_filtered=signal_lowlpfiltered;

end