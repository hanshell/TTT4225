function [ ] = addPitch( wasVoiced, pitch, prevPitchPos, pitchPeriod, start, stop )
%UNTITLED Summary of this function goes here
%   Detailed explanation goes here
    nxtIndex = start;
    while nxtIndex <= stop;
        if wasVoiced;
            pitch(prevPitchPos+pitchPeriod) = 1;
        else
            pitch(nxtIndex) = 1;
        end
        nxtIndex = nxtIndex + pitchPeriod;
        prevPitchPos = prevPitchPos+pitchPeriod;
    end

end

