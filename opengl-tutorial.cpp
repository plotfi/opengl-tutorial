#include "opengl-tutorial.h"

// An array of 3 vectors which represents 3 vertices
static const GLfloat g_vertex_buffer_data[] = {
   1.0f,  1.0f, 0.001f,
  -1.0f,  1.0f, 0.001f,
   1.0f, -1.0f, 0.001f,

  -1.0f, -1.0f, 0.001f,
  -1.0f,  1.0f, 0.001f,
   1.0f, -1.0f, 0.001f,

   1.0f,  0.999f, -0.0f,
   1.0f, -1.0f, -0.0f,
   1.0f, -1.0f, -1.0f,

   1.0f, -1.0f, -1.0f,
   1.0f,  0.999f, -1.0f,
   1.0f,  0.999f, -0.0f,

   1.0f,  1.0f, 0.0f,
  -1.0f,  1.0f, 0.0f,
   1.0f,  1.0f, -1.0f,

   1.0f,  1.0f, -1.0f,
  -1.0f,  1.0f, -1.0f,
  -1.0f,  1.0f, 0.001f,


   1.0f,  1.0f, 1.002f,
  -1.0f,  1.0f, 1.002f,
   1.0f, -1.0f, 1.002f,

  -1.0f, -1.0f, 1.002f,
  -1.0f,  1.0f, 1.002f,
   1.0f, -1.0f, 1.002f,

   1.0f,  0.999f, 1.001f,
   1.0f, -1.0f, 1.001f,
   1.0f, -1.0f, 0.001f,

   1.0f, -1.0f, 0.001f,
   1.0f,  0.999f, 0.001f,
   1.0f,  0.999f, 1.001f,

   1.0f,  1.0f, 1.001f,
  -1.0f,  1.0f, 1.001f,
   1.0f,  1.0f, 0.001f,

   1.0f,  1.0f, 0.001f,
  -1.0f,  1.0f, 0.001f,
  -1.0f,  1.0f, 1.002f,

};

void initGLEW() {
  if (glewInit() == GLEW_OK)
    return;
  fprintf(stderr, "Failed to initialize GLEW\n");
  exit(EXIT_FAILURE);
}

int main() {

  glewExperimental = true; // Needed for core profile
  GLFWwindow *window = initGLFW();
  if (!window)
    return -1;

  glewExperimental = true;
  initGLEW();

  GLuint VertexArrayID;
  glGenVertexArrays(1, &VertexArrayID);
  glBindVertexArray(VertexArrayID);

  GLuint programID = LoadShaders("SimpleVertexShader.vertexshader",
                                 "SimpleFragmentShader.fragmentshader");

  // Get a handle for our "MVP" uniform
  GLuint MatrixID = glGetUniformLocation(programID, "MVP");

  // Projection matrix : 45° Field of View, 4:3 ratio, display range : 0.1 unit
  // <-> 100 units
  glm::mat4 Projection =
  //    glm::perspective(glm::radians(45.0f), 4.0f / 3.0f, 0.1f, 100.0f);
  glm::ortho(-10.0f,10.0f,-10.0f,10.0f,0.0f,100.0f);
  // // In world coordinates

  // Camera matrix
  glm::mat4 View = glm::lookAt(
      glm::vec3(4, 3, 3), // Camera is at (4,3,3), in World Space
      glm::vec3(0, 0, 0), // and looks at the origin
      glm::vec3(0, 1, 0)  // Head is up (set to 0,-1,0 to look upside-down)
  );
  // Model matrix : an identity matrix (model will be at the origin)
  glm::mat4 Model = glm::mat4(1.0f);
  glm::mat4 MVP = Projection * View * Model;

  // Create VAO??
  // This will identify our vertex buffer
  GLuint vertexbuffer;
  // Generate 1 buffer, put the resulting identifier in vertexbuffer
  glGenBuffers(1, &vertexbuffer);
  // The following commands will talk about our 'vertexbuffer' buffer
  glBindBuffer(GL_ARRAY_BUFFER, vertexbuffer);
  // Give our vertices to OpenGL.
  glBufferData(GL_ARRAY_BUFFER, sizeof(g_vertex_buffer_data),
               g_vertex_buffer_data, GL_STATIC_DRAW);

 glClearColor(1.0f, 0.0f, 1.0f, 0.0f);

  while (true) {

    // Clear the screen
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    // Use our shader
    glUseProgram(programID);

    // Send our transformation to the currently bound shader, 
    // in the "MVP" uniform
    glUniformMatrix4fv(MatrixID, 1, GL_FALSE, &MVP[0][0]);

    // 1st attribute buffer : vertices
    glEnableVertexAttribArray(0);
    glBindBuffer(GL_ARRAY_BUFFER, vertexbuffer);
    glVertexAttribPointer(0, // attribute 0. No particular reason for 0, but
                             // must match the layout in the shader.
                          3, // size
                          GL_FLOAT, // type
                          GL_FALSE, // normalized?
                          0,        // stride
                          (void *)0 // array buffer offset
    );

    // Draw the triangle !
    glDrawArrays(GL_TRIANGLES, 0, sizeof(g_vertex_buffer_data) / (g_vertex_buffer_data[0] * 3));
    glDisableVertexAttribArray(0);

    // Swap buffers
    glfwSwapBuffers(window);
    glfwPollEvents();

    // Check if the ESC key was pressed or the window was closed
    if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS ||
        glfwWindowShouldClose(window) != 0)
      break;
  }

  return 0;
}

