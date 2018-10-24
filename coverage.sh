#!/bin/bash

BUILD_DIR=$1
TEST_BIN=$2

cd $BUILD_DIR
export CXX=/usr/bin/g++
cmake .. -DCMAKE_BUILD_TYPE=DEBUG
make
./$TEST_BIN

lcov -c -d CMakeFiles -o cov.info
genhtml cov.info -o out
xdg-open out/index.html
