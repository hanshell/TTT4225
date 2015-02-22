function [ temp_pitches , prevPp ] = addPitch( wasVoiced, prevPitchPos, pitchPeriod, start, stop )
%UNTITLED Summary of this function goes here
%   Detailed explanation goes here
    %nxtIndex = start;
    prevPp = 0;
    temp_pitches = zeros(1,(stop-start)+1);
    length(temp_pitches)

        if wasVoiced;
            temp_pitches((start - prevPitchPos + pitchPeriod)  : pitchPeriod : stop) = 1;
         
        else

            temp_pitches(1 : pitchPeriod : end) = 1
            
        end
    %    nxtIndex = nxtIndex + pitchPeriod;
     %   prevPitchPos = prevPitchPos+pitchPeriod;
        

end

