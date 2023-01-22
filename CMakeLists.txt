project(opengl-tutorial)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

find_package(OpenGL REQUIRED)

include_directories(${OPENGL_INCLUDE_DIRS})
set(CMAKE_CXX_FLAGS "-std=c++17 -Wc++17-extensions -lGLEW -lglfw -I${OGL_ROOT}/include -L${OGL_ROOT}/lib")

add_executable(opengl-tutorial.exe helpers.cpp opengl-tutorial.cpp)
target_link_libraries(opengl-tutorial.exe ${OPENGL_LIBRARY})
