#!/bin/bash

if [ ! -e build ]; then
    mkdir build
fi

cd build/
cmake ..
make
./space-invaders-3d