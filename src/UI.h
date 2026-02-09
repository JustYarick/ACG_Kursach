#pragma once

struct GLFWwindow;
struct Config;

class UI {
public:
  void Init(GLFWwindow *window);
  void BeginFrame();
  void Render(Config &config);
  void EndFrame();
  void Shutdown();
};
