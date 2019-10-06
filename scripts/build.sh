#!/bin/bash

echo "########################################"
echo "Building ..."

mkdir build
cd build
LOG_DEBUG=1 cmake ../src
make -j6
