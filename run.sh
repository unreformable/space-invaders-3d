#!/bin/bash

if [ ! -e build ]; then
    mkdir build
fi

cd build/
cmake ..
make
cd release/
./space-invaders-3d