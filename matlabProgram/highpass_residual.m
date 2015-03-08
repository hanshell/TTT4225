function [ hpfiltered_signal, total_signal ] = highpass_residual( loworder_lp_signal )
%UNTITLED2 Summary of this function goes here
%   Detailed explanation goes here
b=fir1(420, 0.2, 'high');


signal_hpfiltered=zeros(length(loworder_lp_signal(:, 1)), length(loworder_lp_signal));


for i=1:length(loworder_lp_signal(:, 1));
    temp_frame=loworder_lp_signal(i, :);
    
    temp_hpfiltered=filter(b, 1, temp_frame);
    
    signal_hpfiltered(i, :)=temp_hpfiltered;
end

total_signal=[];

for i=1:length(signal_hpfiltered(:, 1));
    for j=1:length(signal_hpfiltered(i, :));
        total_signal=[total_signal ; signal_hpfiltered(i, j)];
    end
end


hpfiltered_signal=signal_hpfiltered;

end