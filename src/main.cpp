#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include "UI.h"
#include "Config.h"

#include <iostream>

int main() {
  glfwInit();

  glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
  glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
  glfwWindowHint(GLFW_OPENGL_CORE_PROFILE, GLFW_OPENGL_CORE_PROFILE);

  GLFWwindow *window =
      glfwCreateWindow(1280, 720, "Collision Simulation", nullptr, nullptr);

  glfwMakeContextCurrent(window);
  gladLoadGLLoader((GLADloadproc)glfwGetProcAddress);

  Config config;
  UI ui;

  ui.Init(window);

  while (!glfwWindowShouldClose(window)) {
    glfwPollEvents();

    ui.BeginFrame();
    ui.Render(config);

    glClearColor(config.clearColor[0], config.clearColor[1],
                 config.clearColor[2], 1.0f);
    glClear(GL_COLOR_BUFFER_BIT);

    ui.EndFrame();

    glfwSwapBuffers(window);
  }

  ui.Shutdown();
  glfwTerminate();

  return 0;
}
