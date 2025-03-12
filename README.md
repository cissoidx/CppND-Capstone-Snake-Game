# CPPND: Capstone Snake Game Example

This is a starter repo for the Capstone project in the [Udacity C++ Nanodegree Program](https://www.udacity.com/course/c-plus-plus-nanodegree--nd213). The code for this repo was inspired by [this](https://codereview.stackexchange.com/questions/212296/snake-game-in-c-with-sdl) excellent StackOverflow post and set of responses.

<img src="snake_game.gif"/>

The Capstone Project gives you a chance to integrate what you've learned throughout this program. This project will become an important part of your portfolio to share with current and future colleagues and employers.

In this project, you can build your own C++ application or extend this Snake game, following the principles you have learned throughout this Nanodegree Program. This project will demonstrate that you can independently create applications using a wide range of C++ features.

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

## Basic Build Instructions

1. Clone this repo.
2. Make a build directory in the top level directory: `mkdir build && cd build`
3. Compile: `cmake .. && make`
4. Run it: `./SnakeGame`.

## New features
1. Allow players to enter their names and save their high scores to a text file. If a player has already a record in this text file, it will be printed out at the start of the game. If the player has reached a higher score, then the score in the record will be updated. 

2. Introduce obstacles. At the start of the game, all obstacles are in a queue behind the scene. Max number of obstable is 3, which can be set in the code. if the snake eats a food and the number of obstacles in game is below 3, it sends a signal and one obstacle appears. Obstacle is a square that has a fixed size of 3. each obstacle has a life time (like 30 seconds), when it expires, the obstacle disappears and goes back to the waiting queue, i.e. the obstacle has a time counter in itself and checks if its life ends. Obstacles do not move. If the snake hit the obstacle, the game ends. An obstacle appears by randomly choosing a place, if it overlaps other stuff (snake/food), try another random place again. 

## Rubric points
1. The submission must compile and run without errors on the Udacity project workspace.
> It does.

2. The project demonstrates an understanding of C++ functions and control structures.
> In obstacle.cpp, there are some functions and control flows, like line 69, the Run function.

3. The project reads data from a file and process the data, or the program writes data to a file.
> In userscore.cpp, there is a class that does the reading and writing.

4. The project accepts user input and processes the input.
> In main.cpp line 19.

5. The project uses data structures and immutable variables.
> Like obstacle.h line 36.

6. One or more classes are added to the project with appropriate access specifiers for class members.
> In userscore.h/cpp, there is a UserScoreManager class.

7. Class constructors utilize member initialization lists.
> In obstacle.cpp line 40, there is a initialization list

8. Classes abstract implementation details from their interfaces.
> Like in obstacle.h/cpp, the function names reflect the functionalities.

9. The project uses destructors appropriately.
> In game.cpp line 18.

10. The project uses move semantics to move data instead of copying it, where possible.
> In obstacle.cpp line 18.

11. The project uses smart pointers instead of raw pointers.
> In game.h line 45.

12. The project uses multithreading.
> In game.cpp line 87.

13. A promise and future is used in the project.
> In game.cpp line 96. 

14. A mutex or lock is used in the project.
> In obstacle.cpp line 71.




## CC Attribution-ShareAlike 4.0 International


Shield: [![CC BY-SA 4.0][cc-by-sa-shield]][cc-by-sa]

This work is licensed under a
[Creative Commons Attribution-ShareAlike 4.0 International License][cc-by-sa].

[![CC BY-SA 4.0][cc-by-sa-image]][cc-by-sa]

[cc-by-sa]: http://creativecommons.org/licenses/by-sa/4.0/
[cc-by-sa-image]: https://licensebuttons.net/l/by-sa/4.0/88x31.png
[cc-by-sa-shield]: https://img.shields.io/badge/License-CC%20BY--SA%204.0-lightgrey.svg
