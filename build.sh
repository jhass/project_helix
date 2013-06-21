#!/bin/sh
target=$1
if [ -z "$target" ]; then
  target=project_helix
  shift
fi

mkdir -p build
cd build
cmake $* .. && make "$target" && exec "./src/$target"
