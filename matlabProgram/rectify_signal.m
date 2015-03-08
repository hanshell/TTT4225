function [ rectified_signal, total_signal ] = rectify_signal( interpolated_signal )
%UNTITLED4 Summary of this function goes here
%   Detailed explanation goes here

signal_rectified=zeros(length(interpolated_signal(:, 1)), length(interpolated_signal));

for i=1:length(interpolated_signal(:, 1));
     temp_frame=interpolated_signal(i, :);
     temp_rectified=abs(temp_frame);
     signal_rectified(i, :)=temp_rectified;
end

total_signal=[];


for i=1:length(signal_rectified(:, 1));
    for j=1:length(signal_rectified(i, :));
        total_signal=[total_signal ; signal_rectified(i, j)];
    end
end


rectified_signal=signal_rectified;

end