#pragma once
#include "core/Simulation.h"
#include "render/Renderer.h"
struct GLFWwindow;
struct Config;

class UI {
public:
  void Init(GLFWwindow *window);
  void BeginFrame();
  void EndFrame();
  void Render(Config &config, Simulation &sim, Renderer &renderer);
  void Shutdown();
};
