#!/bin/bash
# script to build the raspberry pi binary in bash
# this is not a build system its just a really simple script so I dont have
# to remember all the libraries
gcc -o sccec_stair_piano sccec_stair_piano.cpp `sdl-config --cflags --libs` -lSDL_mixer
