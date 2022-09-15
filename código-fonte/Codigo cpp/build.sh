#!/bin/bash

mkdir build && cd build
cmake ..
cmake --build . --config Release
cd ..
./build/fastFaceLandmarkDetection
echo "Apagando os dados"
#rm -rf build
echo "FIM!"
