
# Nibbler

Epitech project : 
We have to make a clone of the famous Snake game. We have to dynamically load the graphic part which are shared library.
We are two to make this project.

## How to
* First install dependencies : apt-get install libsdl1.2-dev libsdl-image1.2-dev libsdl-gfx1.2-dev libglib2.0-dev
* Compile : make
* Start the game : ./nibbler x y ./graphic_library (x and y are the terrain size)

## Feature
* Press escape to restart the game
* Use arrow key to move your snake
* Press space to use boost !
* They are two portal on the map, you can pass throught ;)

## Example
* ./nibbler 20 20 ./lib_nibbler_sdl.so 
![alt text](https://github.com/Aschen/Nibbler/raw/master/images/SDL.png "lib_nibbler_sdl.so")
* ./nibbler 40 40 ./lib_nibbler_ncurses.so
![alt text](https://github.com/Aschen/Nibbler/raw/master/images/NCURSE.png "lib_nibbler_ncurses.so")
* ./nibbler 20 20 ./lib_nibbler_opengl.so
![alt text](https://github.com/Aschen/Nibbler/raw/master/images/OPENGL.png "lib_nibbler_opengl.so")
