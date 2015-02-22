filename = 'files/anvsb1.wav';

% Read audiofile. y is the data, Fs is the sampling rate
[ y, Fs ] = audioread( filename );

% select wanted segment of data
k = y( 16000:16700 );

% Get the coefficients from the signal k
[ coeff,E ] = lpc( k, 20 );

% Returns length(k) point complex frequency response
% if the first is [1 -.95] preemphasis filter
[ H,W ] = freqz( [1 -.95], coeff, length(k) );
% Filter the signal k, and get the LPC error signal. Since the voice signal
% is y in x -> h -> y we have to send it through the inverse filter
% The vocal tract system can be modeled as a time-varying all-pole filter 
% using segmental analysis. Thus the inverse is an all-zero filter.
e = filter( coeff, 1, k );
% Inverse the LPC error signal
k_inv = filter( 1, coeff, e );

figure
hold on
subplot( 3,1,1 )
% Plot the absolute value since H is the complex frequency response
plot( W, abs(H) )
subplot( 3,1,2 )
% Plot of a litte part of the complete signal
plot( k )
% Plot the corresponding LPC error signal
subplot( 3,1,3 )
plot( e )

figure
plot( k_inv )


