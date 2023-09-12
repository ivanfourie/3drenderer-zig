# Software 3D Renderer project

A project written in C (C99) & SDL to explore writing a software 3D renderer from scratch. It makes use of Zig for building and the main process to support multiple platfrom targets. 

![Rendered F22 model](./assets/f22.gif?raw=true)

It is based on the following online course by Gustavo Pezzi: https://courses.pikuma.com/courses/learn-computer-graphics-programming

# Dependencies

The main dependency of this project is the [Simple DirectMedia Layer 2](https://www.libsdl.org/) library. Make sure it is installed on your platform.

# Building and running

To build the project

    zig build

To run the executable

    zig build run

# Input keys

* `1`: Show the wireframe and a small red dot for each triangle vertex
* `2`: Show only the wireframe lines
* `3`: Show filled triangles with a solid color
* `4`: Show both filled triangles and wireframe lines
* `5`: Show textured triangles
* `6`: Show textured triangles with a wireframe
* `c`: Toggle back-face culling
* `r`: Toggle automatic rotation
* `Up`: Move camera up
* `Down`: Move camera down
* `w`: Move camera forward 
* `s`: Move camera backward
* `a`: Yaw camera to the left
* `d`: Yaw camera to the right
* `Left`: Rotate left (y-axis)
* `Right`: Rotate right (y-axis)
* `.`: Increase rotation rate
* `,`: Decrease rotation rate

# Credits
* The incredibly fun [3D Graphics Programming from Scratch](https://courses.pikuma.com/courses/learn-computer-graphics-programming) course by Gustavo Pezzi
* `f22.obj`, `efa.obj`, and `f117.obj` aircraft files were created by Artem Katrych.
* `crab.obj` file was created by [Bohdan Lvov](https://sketchfab.com/ostapblendercg)
* `drone.obj` file was created by [Willy Decarpentrie](https://sketchfab.com/skudgee).