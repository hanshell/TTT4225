function [ res ] = getResidual( s, n_frame, n_step)
%getResidual returns the residual signal
%   reads an audiofile and does LP-analysis on it. Inverse-filter the
%   signals to get the residual signal.

    % Some constants
    n_sig = length(s);
    n_iter = ceil((n_sig - n_frame) / n_step) + 1; 
    padding = zeros((n_frame + n_step * n_iter -1) - n_sig - 1 ,1); % the padding we need to fill the n_iter'th signal
    s = [s ; padding];
    n_sig = length(s); % length of the signal


    res = zeros(n_sig, 1);
    
    for i = 1 : n_iter;
        frame = getFrame(i, s, n_frame, n_step); % returns the ith part of the sound signal
        frame_ham = frame .* hamming(n_frame);
    
        coeffs = lpc(frame_ham, 14); % Find the short-time coefficients for the ith part of the signal.
    
        frame_residual = filter(coeffs, 1, frame_ham); % filter the ith signal, producing the ith residual signal

    
        if i == 1;
            res(1 : n_frame) = frame_residual; % first iteration we can add everything to the res signal
        
        else
            % en all but the first iteration we first add the previous signal and the current signal in the overlapping area.
            % after that we add the rest of the signal
            res( ((i-1)*n_step) + 1 : (n_frame + (i-2)*n_step) ) = res( ((i-1)*n_step) + 1 : (n_frame + (i-2)*n_step) ) + frame_residual(1: (n_frame - n_step));
            res( (n_frame + (i-2)*n_step) +1 : i*n_step+(n_frame - n_step) ) = frame_residual(n_frame - n_step + 1 : end);
        end
    end
    res = res(1: end - length(padding)); % remove padding from residual signal

end

