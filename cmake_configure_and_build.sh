#!/usr/bin/env bash

if [[ "$OSTYPE" == "linux-gnu"* ]]; then
    # For Linux only; required for the `cmake --build` command to work with the correct version
    # of gcc which fully supports C++20 and the `std::format` library.
    export CC=gcc-13
    export CXX=g++-13
fi

echo "==================================================================="

if [ "$1" == "debug" ]; then
    echo "Configuring and building debug..."
    cmake --preset Debug
    cmake --build --preset Debug
elif [ "$1" == "release" ]; then
    echo "Configuring and building release..."
    cmake --preset Release
    cmake --build --preset Release
fi
