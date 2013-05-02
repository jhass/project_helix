#!/bin/sh
mkdir -p build
cd build
cmake ..
make
./project_helix
