#!/bin/bash
mkdir build-em

cd build-em

cmake -DCMAKE_TOOLCHAIN_FILE=cmake/Emscripten.cmake -DCMAKE_CXX_FLAGS="-o file.html --preload-file assets" -DCMAKE_EXE_LINKER_FLAGS="-o index.html" -DCMAKE_BUILD_TYPE=Debug -G "Unix Makefiles" ..

cp ../cmake/index.html index.html