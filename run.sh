#!/bin/bash

if [ ! -e build ]; then
    mkdir build
fi

cd build/
cmake ..
make
cd game/
./space-invaders-3d