#!/bin/bash
# first, we build catch2 and install it to a subfolder
pushd extern/catch2
cmake -B".build" -H. -DBUILD_TESTING=OFF -DCMAKE_INSTALL_PREFIX=../../install/catch2 -DCATCH_BUILD_STATIC_LIBRARY=ON
cmake --build ".build/" --target install
popd 

# googletest and doctest can simply be added as subdirectory
mkdir -p build
cd build
cmake ..
make
