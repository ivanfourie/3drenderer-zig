# Software 3D Renderer project

A project written in C (C99) & SDL to explore writing a software 3D renderer almost from scratch.

This is entirely based on the following online course: https://courses.pikuma.com/courses/learn-computer-graphics-programming

# Dev environment

To develop the project in GNU/Linux I am using WSL on Windows 10 using VcXsrv to render to a window. It also seems fine using WSLg. Some caveats apply in full screen mode in SDL that forced me to use windowed mode for the time being. 

I am exploring the project in Visual Studio C++ on Windows at the same time here: https://github.com/ivan-fourie/3drenderer-win

# Dependencies

The main dependency of this project is the SDL2 library. Make sure `libsdl2-dev` is installed on your distro using its package manager.

# Building and runnning

To build the project

    make

To run it

    make run