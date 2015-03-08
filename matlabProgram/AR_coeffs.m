function [ coeffs ] = AR_coeffs( signal, Fs )
%UNTITLED Summary of this function goes here
%   Detailed explanation goes here
    coeffs = lpc(signal, 14);
end

