function [ interpolated_signal, total_signal ] = interpolate_signal_by_frame( signal, interpolation_value )
%UNTITLED3 Summary of this function goes here
%   Interpolates a 2D-signal frame-by-frame by a given interpolation value

signal_interpolated=zeros(length(signal), length(signal(1, :))*interpolation_value);

for i=1:length(signal);
     temp_frame=signal(i, :);
     temp_interpolate=interp(temp_frame, interpolation_value);
     signal_interpolated(i, :)=temp_interpolate;

end

total_signal=[];
length(signal)
length(signal_interpolated(1, :))
size(signal_interpolated)
for i=1:length(signal);
    for j=1:length(signal_interpolated(i, :));
        total_signal=[total_signal ; signal_interpolated(i, j)];
    end
end


interpolated_signal=signal_interpolated;


en