#pragma once
#include <glm/glm.hpp>
#include "core/Body.h"

class Renderer {
public:
  void Init();
  void Shutdown();

  void DrawCircle(const Body &body);

private:
  unsigned int VAO, VBO;
  unsigned int shaderProgram;

  void CreateCircleMesh();
  unsigned int CreateShader();
};
