# PiE C++ project

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