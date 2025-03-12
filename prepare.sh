#!/bin/bash

sudo apt install assimp-utils libassimp-dev libassimp5
sudo apt install c++ gcc cmake make 

#Do TIFF library compilation (the first time)
cd ./TIFF/tifflib
cmake -B ./build -S . -DBUILD_SHARED_LIBS=OFF
cd ./build/
make

