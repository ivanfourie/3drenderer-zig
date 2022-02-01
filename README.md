# Software 3D Renderer project

A project written in C (C99) & SDL to explore writing a software 3D renderer almost from scratch.

![Rendered F22 model](./assets/screenshot-f22.png?raw=true|width=250)

It entirely based on the following online course: https://courses.pikuma.com/courses/learn-computer-graphics-programming

# Platforms

This project uses the GNU C Compiler toolchain and should theorically work on those that supports and SDL. 

## Windows
### Windows 11: WSL2 and WSLg
You can build and run project in a distro of your choice using WSL2 and WSLg on Windows 11. 

### Windows 10: WSL2 and VcXsrv
You can build and run project in a distro of your choice using WSL2 and VcXsrv on Windows 10. Using VcXsrv will require some configuration in your distro. Some caveats apply in full screen mode in SDL so you can edit the code to use windowed mode instead. 

### Windows using MSVC
I am exploring the project in Visual Studio C++ on Windows at the same time here: https://github.com/ivan-fourie/3drenderer-win

### Windows using MinGW (Experimental)
You will need to make sure to install the MinGW Development Libraries from https://www.libsdl.org/download-2.0.php

Running in MinGW will require some tweaking with the compiler flags:

`gcc -Wall -std=c99 ./src/*.c -fcommon -lmingw32 -lSDL2main -lSDL2 -lm -o renderer`

You will also need to change `#include <SDL.h>` to `#include <SDL2/SDL.h>` in `main.c`

To run after building the binary, make sure to place SLD2.dll in the same folder as the executable. You can get it from the SDL2 windows runtime libaries here: https://www.libsdl.org/download-2.0.php. Make sure that the dll you use matches the platform you compiled it for.

# Dependencies

The main dependency of this project is the SDL2 library. Make sure `libsdl2-dev` is installed on your distro using its package manager.

# Building and runnning

To build the project

    make

To run it

    make run

# Credits
* The incredibly fun [3D Graphics Programming from Scratch](https://courses.pikuma.com/courses/learn-computer-graphics-programming) course by Gustavo Pezzi
* `f22.obj`, `efa.obj`, and `f117.obj` aircraft files were created by Artem Katrych.
* `crab.obj` file was created by [Bohdan Lvov](https://sketchfab.com/ostapblendercg)
* `drone.obj` file was created by [Willy Decarpentrie](https://sketchfab.com/skudgee).