# PiE C++ project

[![Build Status](https://travis-ci.com/Jvanrhijn/pie-project-untitled.svg?branch=master)](https://travis-ci.com/Jvanrhijn/pie-project-untitled)
[![codecov](https://codecov.io/gh/Jvanrhijn/pie-project-untitled/branch/master/graph/badge.svg)](https://codecov.io/gh/Jvanrhijn/pie-project-untitled)

This project implements an interactive math puzzle, played as follows:

* Draw a square grid, of `N` by `N` squares.
* Start in any square on the grid, and write a `1` in it.
* From this square, move over to any other square which is either two squares removed horizontally
 or vertically, or one square diagonally. E.g. from the square at position `(10, 5)`, you can move to
 `(13, 5)`, `(7, 5)`, `(10, 8)`, `(10, 2)`, `(12, 3)`, etc.
 * Write a `2` in this square.
 * Continue this pattern until the entire grid is filled with the numbers `1` through `N^2`.
 
 The project will implement an interactive version, where the player can choose where to move,
 as well as an automated solver algorithm.

 ### Building

 Clone the repository:

 ```
 $ git clone --recurse-submodules [url]
 ```

Create a build directory,

```
$ mkdir build && cd build
```

Build the source with optimizations:

```
$ cmake -DCMAKE_BUILD_TYPE=RELEASE ..
$ make -j pie
```

### Running

[WIP]

### Testing

See `Building`. Instead of building with optimizations, call cmake as

```
$ cmake -DCMAKE_BUILD_TYPE=DEBUG ..
$ make -j unit_tests
```

This will create the `unit_tests` executable in your build directory:

```
./unit_tests
```

 ### Requirements

General:
* cmake >=3.9.2

For development:
* GTest: https://github.com/google/googletest
 
