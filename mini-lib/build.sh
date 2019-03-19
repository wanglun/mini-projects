#!/bin/bash
DEPENDENCIES_PREFIX=${HOME}/dependencies
export LD_LIBRARY_PATH=${LD_LIBRARY_PATH}:${DEPENDENCIES_PREFIX}/lib

mkdir -p build
cd build && cmake -DCMAKE_PREFIX_PATH=${DEPENDENCIES_PREFIX} .. && make VERBOSE=1 -j1
