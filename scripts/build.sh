#!/bin/bash

echo "########################################"
echo "Building ..."

if [ -d "build" ]; then
  cd build
else
  mkdir build
  cd build
  LOG_DEBUG=1 cmake ../src
fi

make -j6
