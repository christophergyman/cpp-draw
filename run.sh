#!/bin/bash

# Check if build directory exists
if [ -d "build" ]; then
  echo "Build directory exists. Removing it..."
  rm -rf build
fi

# Create empty build directory
echo "Creating build directory..."
mkdir build

# Go into directory
cd build

# Run cmake
echo "Running cmake..."
cmake ../

# Run make
echo "Running make..."
make

# Run application
./MyGLFWApp
