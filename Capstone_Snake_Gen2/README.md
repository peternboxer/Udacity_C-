# CPPND: C++ Nanodegree Capstone Project - Snake Game 2.0
The program provided Snake game is chosen to pursue the Capstone project.

## Basic Build Instructions

1. Make a build directory in the top level directory: `mkdir build && cd build`
3. Compile: `cmake .. && make`
4. Run it: 
  a. Single mode: `./SnakeGame -s`.
  b. Battle mode: `./SnakeGame -m`.
  c. Help page: `./SnakeGame -h`.

## 2.0 New Features

New features have been added to the original ver.1.0 game with the followings:

1. Mode selection including default "single mode" and new "battel mdode".

2. "battle mode" is added to allow user compete with built-in AI.

3. Dynamic difficulty (AI speed) is implemented in the "battle mode".

## 2.0 revision

1. A "Enemy" class is created and inherited from "Snake" class.

2. Upon game start, enemy is created (allocated & de-allocated with uniqe_ptr) and autonomously move to the food based on the position coordinate of food and itself.

3. Same as player's snake, the enemy's body would also grow upon getting "food".

4. Dynamic difficulty: The moving speed of the enemy dynamically adjusts depending on player's performance.

## Rubris Points Coverage in this project

1. README (All Rubric Points REQUIRED)
  - A README with instructions is included with the project
  - The README indicates which project is chosen.
  - The README includes information about each rubric point addressed.

2. Compiling and Testing (All Rubric Points REQUIRED)
  - The submission must compile and run.

3. Loops, Functions, I/O
  - The project demonstrates an understanding of C++ functions and control structures.
  - The project accepts user input and processes the input.

4. Object Oriented Programming
  - The project uses Object Oriented Programming techniques.
  - Classes use appropriate access specifiers for class members.
  - Class constructors utilize member initialization lists.
  - Classes abstract implementation details from their interfaces.
  - Classes encapsulate behavior.
  - Classes follow an appropriate inheritance hierarchy.

5. Memory Management
  - The project makes use of references in function declarations.
  - The project uses destructors appropriately.
  - The project uses scope / Resource Acquisition Is Initialization (RAII) where appropriate.
  - The project uses smart pointers instead of raw pointers.

## Dependencies for Running Locally
* cmake >= 3.7
  * All OSes: [click here for installation instructions](https://cmake.org/install/)
* make >= 4.1 (Linux, Mac), 3.81 (Windows)
  * Linux: make is installed by default on most Linux distros
  * Mac: [install Xcode command line tools to get make](https://developer.apple.com/xcode/features/)
  * Windows: [Click here for installation instructions](http://gnuwin32.sourceforge.net/packages/make.htm)
* SDL2 >= 2.0
  * All installation instructions can be found [here](https://wiki.libsdl.org/Installation)
  >Note that for Linux, an `apt` or `apt-get` installation is preferred to building from source. 
* gcc/g++ >= 5.4
  * Linux: gcc / g++ is installed by default on most Linux distros
  * Mac: same deal as make - [install Xcode command line tools](https://developer.apple.com/xcode/features/)
  * Windows: recommend using [MinGW](http://www.mingw.org/)



## CC Attribution-ShareAlike 4.0 International


Shield: [![CC BY-SA 4.0][cc-by-sa-shield]][cc-by-sa]

This work is licensed under a
[Creative Commons Attribution-ShareAlike 4.0 International License][cc-by-sa].

[![CC BY-SA 4.0][cc-by-sa-image]][cc-by-sa]

[cc-by-sa]: http://creativecommons.org/licenses/by-sa/4.0/
[cc-by-sa-image]: https://licensebuttons.net/l/by-sa/4.0/88x31.png
[cc-by-sa-shield]: https://img.shields.io/badge/License-CC%20BY--SA%204.0-lightgrey.svg
