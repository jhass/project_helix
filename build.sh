#!/bin/sh
target=$(shift)
if [ -z "$target" ]; then
  target=project_helix
fi

mkdir -p build
cd build
cmake $* .. && make "$target" && exec "./src/$target"
