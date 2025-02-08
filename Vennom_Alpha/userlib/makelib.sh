#!/bin/bash

if [ "$#" -ne 1 ]; then
	echo "Usage: ./makelib.sh <file.cc>"
	exit 1
fi

if [ ! -f "$1" ]; then
    echo -e "\e[91mFile: $1 not found!\e[39m"
    exit 1
fi

echo "Building $1..."

fname=$1
fname_noext="${fname%.*}"
lib_str="lib"
so_str=".so"
so1_str=".so.1"
o_str=".o"

lib1_fname=$lib_str$fname_noext$so1_str
lib_fname=$lib_str$fname_noext$so_str
obj_fname=$fname_noext$o_str

g++ -O3 -fPIC -c $fname
g++ -shared -Wl,-soname,$lib1_fname -o $lib_fname $obj_fname
rm *.o

if [ $? -eq 0 ]; then
	echo -e "\e[32m$lib_fname : Custom library successfully generated!\e[39m"
else
	echo -e "\e[91mError! \e[39mFailed to build library."
fi
