#!/bin/sh
if [ -z "$1" ]; then
  target=project_helix
else
  target=$1
fi

mkdir -p build
cd build
cmake .. && make "$target" && exec "./$target"
