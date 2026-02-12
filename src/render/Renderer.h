#pragma once
#include <glm/glm.hpp>
#include <memory>

#include "core/Body.h"
#include "render/shaders/Shader.h"

class Renderer {
public:
  void Init();
  void Shutdown();

  void SetProjection(float width, float height);
  void Draw(const Body &body);

  Shader *GetDefaultShader();

private:
  std::unique_ptr<Shader> circleShader;

  unsigned int VAO = 0;
  unsigned int VBO = 0;

  void CreateCircleMesh();

  glm::mat4 projection;
};
