# Hopscotch

[![Build Status](https://travis-ci.com/Jvanrhijn/hopscotch.svg?branch=master)](https://travis-ci.com/Jvanrhijn/hopscotch)
[![codecov](https://codecov.io/gh/Jvanrhijn/hopscotch/branch/master/graph/badge.svg)](https://codecov.io/gh/Jvanrhijn/hopscotch)

This project implements an interactive math puzzle, played as follows (description from [here](https://puzzling.stackexchange.com/questions/20238/explore-the-square-with-100-hops)):

<p align="center">
   <img src="https://i.imgur.com/SSlJ7UD.png">
</p>


> The rules are simple: Given a grid of `N x N` squares, your task is to visit every square exactly once. In each step, you may
>
>    * skip 2 squares horizontally or vertically or
>    * skip 1 square diagonally

 ### Features
 
 * Interactive mode, where the user chooses their path through the grid.
 * Automated mode: will generate a solution by employing a depth-first search
 with Warnsdorff's rule as a heuristic.

 ### Requirements

* cmake >=3.9.2
* OpenGL 3.3 core
* [GLFW3](https://www.glfw.org/)

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
$ make -j hopscotch 
```

### Running

Run the executable from the repository root directory:

```
$ /home/.../hopscotch/build/src/hopscotch
```

Legal moves will be highlighted in green. To quit the game, press `ESC` or `Q`. To
reset the board, press `R`.

By default, the game will start in the upper left corner, with a board size of `5 x 5`,
with a window resolution of `600 x 600`.
The game mode can be changed by supplying command line arguments:

* `-r` and `-c` set the starting row and column, indexed with 0.
* `-n` sets the size of the board.
* `-w` sets the width of the window in pixels.
* `-a` automatically solves the game. 
* `-i` sets the number of iterations to attempt in the autosolver.

For example,

```
$ ./build/src/hopscotch -n 8 -r 1 -w 900
```

will start the game with an `8 x 8` grid, starting in row 1, in a window of `900 x 900`
pixels.

### Testing

See `Building`. Instead of building with optimizations, call cmake as

```
$ cmake -DCMAKE_BUILD_TYPE=DEBUG ..
$ make -j unit_tests
```

This will create the `unit_tests` executable in your build directory:

```
./build/tests/unit_tests
```
