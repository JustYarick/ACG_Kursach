#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <imgui.h>

#include "ui/UI.h"
#include "Config.h"
#include "core/Simulation.h"
#include "render/Renderer.h"

int main() {
  glfwInit();
  glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
  glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
  glfwWindowHint(GLFW_OPENGL_CORE_PROFILE, GLFW_OPENGL_CORE_PROFILE);

  GLFWwindow *window =
      glfwCreateWindow(1280, 720, "2D Collision Simulation", nullptr, nullptr);

  glfwMakeContextCurrent(window);
  gladLoadGLLoader((GLADloadproc)glfwGetProcAddress);

  glViewport(0, 0, 1280, 720);

  Config config;
  UI ui;
  Simulation simulation;
  Renderer renderer;

  ui.Init(window);
  renderer.Init();
  simulation.Reset(config);

  float lastTime = glfwGetTime();
  int width, height;
  glfwGetFramebufferSize(window, &width, &height);
  glViewport(0, 0, width, height);
  simulation.SetWorldBounds((float)width, (float)height);

  while (!glfwWindowShouldClose(window)) {
    float currentTime = glfwGetTime();
    float dt = currentTime - lastTime;
    lastTime = currentTime;

    glfwPollEvents();

    ui.BeginFrame();
    ui.Render(config, simulation);

    if (config.simulationRunning)
      simulation.Update(dt, config);

    glClearColor(config.clearColor[0], config.clearColor[1],
                 config.clearColor[2], 1.0f);
    glClear(GL_COLOR_BUFFER_BIT);

    renderer.DrawCircle(simulation.GetBody1());
    renderer.DrawCircle(simulation.GetBody2());

    glm::vec2 momentum = simulation.GetTotalMomentum();

    ui.EndFrame();
    glfwSwapBuffers(window);
  }

  renderer.Shutdown();
  ui.Shutdown();
  glfwTerminate();
}
