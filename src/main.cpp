#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>

#include "ui/UI.h"
#include "Config.h"
#include "core/Simulation.h"
#include "render/Renderer.h"
#include "AppContext.h"

static void framebuffer_size_callback(GLFWwindow *window, int width,
                                      int height) {
  glViewport(0, 0, width, height);

  auto *ctx = static_cast<AppContext *>(glfwGetWindowUserPointer(window));
  if (!ctx)
    return;

  ctx->renderer->SetProjection(width, height);
  ctx->simulation->SetWorldBounds(width, height);
}

int main() {
  glfwInit();
  glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
  glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
  glfwWindowHint(GLFW_OPENGL_CORE_PROFILE, GLFW_OPENGL_CORE_PROFILE);

  GLFWwindow *window =
      glfwCreateWindow(1280, 720, "2D Collision Simulation", nullptr, nullptr);

  glfwMakeContextCurrent(window);
  gladLoadGLLoader((GLADloadproc)glfwGetProcAddress);

  Config config;
  UI ui;
  Simulation simulation;
  Renderer renderer;

  ui.Init(window);
  renderer.Init();

  simulation.Reset(config);

  Body b1(1.0f, 0.2f, {-0.5f, 0.0f}, {1.0f, 0.0f}, {1.0f, 0.0f, 0.0f});

  Body b2(1.0f, 0.2f, {0.5f, 0.0f}, {-1.0f, 0.0f}, {1.0f, 0.0f, 0.0f});
  b1.shader = renderer.GetDefaultShader();
  b2.shader = renderer.GetDefaultShader();

  simulation.AddBody(b1);
  simulation.AddBody(b2);

  int width, height;
  glfwGetFramebufferSize(window, &width, &height);
  glViewport(0, 0, width, height);

  renderer.SetProjection(width, height);
  simulation.SetWorldBounds(width, height);

  AppContext context{&renderer, &simulation};
  glfwSetWindowUserPointer(window, &context);
  glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);

  float lastTime = glfwGetTime();

  while (!glfwWindowShouldClose(window)) {
    float currentTime = glfwGetTime();
    float dt = currentTime - lastTime;
    lastTime = currentTime;

    glfwPollEvents();

    ui.BeginFrame();
    ui.Render(config, simulation, renderer);

    if (config.simulationRunning)
      simulation.Update(dt, config);

    glClearColor(config.clearColor[0], config.clearColor[1],
                 config.clearColor[2], 1.0f);
    glClear(GL_COLOR_BUFFER_BIT);

    for (const auto &body : simulation.GetBodies())
      renderer.Draw(body);

    ui.EndFrame();
    glfwSwapBuffers(window);
  }

  renderer.Shutdown();
  ui.Shutdown();
  glfwTerminate();
}
