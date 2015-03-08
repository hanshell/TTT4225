function [ filtered_signal ] = lowpassFilter( signal )
%UNTITLED2 Summary of this function goes here
%   Detailed explanation goes here
    filename = 'files/original.wav'; % name/location of audiofile to be read
    
    order = 14;
    f = [0 0.1 0.2 0.25 0.35 0.45 0.55 0.65 0.7 1];
    a = [1 1 1 1 0 0 0 0 0 0];
    
    A = firpm(order, f, a);
    [H,w] = freqz(A);
    
    filtered_signal = filter(A,1,signal);
end

