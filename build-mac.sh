#!/bin/bash

# brew install glm glfw glew
HOMEBREW=~/opt/homebrew

clang++ \
  -I$HOMEBREW/include -L$HOMEBREW/lib \
  -Xlinker -framework -Xlinker OpenGL \
  -lGLEW -lglfw \
  *.cpp -o opengl-tutorial.exe

./opengl-tutorial.exe

