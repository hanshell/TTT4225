function [ frame ] = lp_analysis( i, s, n_frame, n_step)
%UNTITLED3 Summary of this function goes here
%   Detailed explanation goes here
    
    if i == 1; % in the first iteration we can send back the 480 first elements.
        frame = s( 1 : n_frame );
    %elseif i == n_iter;
 
    else % Inn all the others we have to carefully select. The startingpoint starts at 320 after the first iter.
        % After this it increments by 320 for every iteration. We also have
        % to add 1 since matlab counts from, to and including. Until
        frame = s( ((i-1)*n_step +1) : i*n_step+(n_frame - n_step));
    end
    
end

