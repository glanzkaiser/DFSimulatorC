# opengl_sandbox

Sandbox app to learn and experiment OpenGl possibilities.
Based on the great OpenGL series of "The Cherno": https://www.youtube.com/playlist?list=PLlrATfBNZ98foTJPJ_Ev03o2oq3-GGOS2

I also used following libraries:
- stb (Load images): https://github.com/nothings/stb
- glm (OpenGL maths): https://github.com/g-truc/glm
- imgui (Graphical User Interface) : https://github.com/ocornut/imgui

## 1 - Installation

First, clone the repository.
```
git clone https://github.com/ThomasParistech/opengl_sandbox.git
```
Then, go to the directory and compile it.
```
cd opengl_sandbox
mkdir build
cd build
cmake ..
make -j6
```
Please note that CMakeLists.txt is configured in a such way that the executable is generated in the "bin" directory.

## 2 - Running

Go to the build directory and run the app
```
bin/main
```
![](./images/demo.gif)