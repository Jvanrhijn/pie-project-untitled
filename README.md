# Hopscotch

[![Build Status](https://travis-ci.com/Jvanrhijn/pie-project-untitled.svg?branch=master)](https://travis-ci.com/Jvanrhijn/pie-project-untitled)
[![codecov](https://codecov.io/gh/Jvanrhijn/pie-project-untitled/branch/master/graph/badge.svg)](https://codecov.io/gh/Jvanrhijn/pie-project-untitled)

This project implements an interactive math puzzle, played as follows (description and image from [here](https://puzzling.stackexchange.com/questions/20238/explore-the-square-with-100-hops)):

[![explanation](https://i.stack.imgur.com/MW0GO.png)](https://i.stack.imgur.com/MW0GO.png)

> The rules are simple: Given a grid of `N x N` squares, your task is to visit every square exactly once. In each step, you may
>
>    * skip 2 squares horizontally or vertically or
>    * skip 1 square diagonally

 
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
* OpenGL 3.3 core
* [GLFW3](https://www.glfw.org/)
* [FreeType](https://www.freetype.org/download.html)

For development:
* GTest: https://github.com/google/googletest
 
