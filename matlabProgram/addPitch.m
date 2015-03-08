function [ temp_pitches , prevPp ] = addPitch( wasVoiced, prevPitchPos, pitchPeriod, start, stop )
%UNTITLED Summary of this function goes here
%   Detailed explanation goes here
    %nxtIndex = start;
    
    temp_pitches = zeros(1,(stop-start)+1);
    N_frame = 320;
        if wasVoiced;
            %disp('Voiced')
            temp_pitches((stop - N_frame)+1 - prevPitchPos + pitchPeriod : pitchPeriod : end) = 1;
            %temp_pitches((start - prevPitchPos) + pitchPeriod : pitchPeriod : end) = 1;
            %disp('temp_pitch voiced')
            %length(temp_pitches)
            
        else
            %disp('unvoiced')
            temp_pitches(1 : pitchPeriod : end) = 1;
            %disp('temp_pitch unvoiced')
            %length(temp_pitches)
        end
        prevPp = start + (max(find(temp_pitches)) - 1);
    %    nxtIndex = nxtIndex + pitchPeriod;
     %   prevPitchPos = prevPitchPos+pitchPeriod;
        

end

