// Include standard headers
#include <stdio.h>
#include <stdlib.h>

// Include GLEW
#include <GL/glew.h>

// Include GLFW
#include <GLFW/glfw3.h>

// Include GLM
#include <glm/glm.hpp>
using namespace glm;

#include <algorithm>
#include <fstream>
#include <iostream>
#include <sstream>
#include <stdio.h>
#include <string>
#include <vector>
using namespace std;

#include <stdlib.h>
#include <string.h>

GLuint LoadShaders(const char *vertex_file_path,
                   const char *fragment_file_path);
GLFWwindow *initGLFW();

