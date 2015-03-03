function [ restored_signal ] = AR_restore( hp_filtered_signal, coefficients )
%UNTITLED3 Summary of this function goes here
%   Detailed explanation goes here
final_signal=[];

signal_restored=zeros(length(hp_filtered_signal(:, 1)), length(hp_filtered_signal));


for i=1:length(coefficients);
    temp_frame=hp_filtered_signal(i, :);
    temp_ARfiltered=filter(1, coefficients(i, :), temp_frame);
    signal_restored(i, :)=temp_ARfiltered;
end

total_signal=[];

for i=1:length(signal_restored(:, 1));
    for j=1:length(signal_restored(i, :));
        total_signal=[total_signal ; signal_restored(i, j)];
    end
end

restored_signal=total_signal;

end