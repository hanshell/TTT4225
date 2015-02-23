function [ gain] = gain_estimation( err_sig )
%UNTITLED Summary of this function goes here
%   Detailed explanation goes here
    power = 0;
    for i = 1:length(err_sig);
        power = power + abs(err_sig(i))^2;
    end
    power = power / length(err_sig);
    gain = sqrt(power);

end

