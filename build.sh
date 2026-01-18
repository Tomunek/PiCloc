#!/bin/bash
set -e

echo "Preparing build"
cmake -S . -B build
cd build 
cmake ..

echo "Building"
ninja -C .

cd ..
echo "Build finished. Upload firmware to Pi Pico:"
echo $(pwd)"/build/picloc.uf2"

