#!/bin/bash

# compile and link the program, remove object files afterwards
make
make clean


# run the program with 3 different filter specs:
# lpcoeff.txt: LP filter, passband 0-1000Hz, stopband 1500-8000Hz
# bpcoeff.txt: BP filter, passband 1500-2500Hz, stopbands 0-1000, 3000-8000Hz
# hpcoeff.txt: HP filter, passband 3000-8000Hz, stopband 0-2500Hz
echo "***********************************"
echo "Low-pass filtering: Filter original.wav lpfiltered.wav lpcoeff.txt"
./Filter original.wav lpfiltered.wav lpcoeff.txt
echo "Band-pass filtering: Filter original.wav bpfiltered.wav bpcoeff.txt"
./Filter original.wav bpfiltered.wav bpcoeff.txt
echo "High-pass filtering: Filter original.wav hpfiltered.wav hpcoeff.txt"
./Filter original.wav hpfiltered.wav hpcoeff.txt

# play the results (substitute na_play with your favourite playprog
echo "***********************************"
echo " "
echo "Playing files:"
echo " "
echo Original
cvlc --play-and-exit original.wav 
echo Low-pass filtered 0-1000Hz 
cvlc --play-and-exit lpfiltered.wav 
echo Band-pass filtered 1500-2500 Hz
cvlc --play-and-exit bpfiltered.wav 
echo High-pass filtered 3000-8000 Hz
cvlc --play-and-exit hpfiltered.wav
