#pragma once
#include "render/shaders/Shader.h"
#include <glm/glm.hpp>

struct Body {
  float mass;
  float radius;

  glm::vec2 position;
  glm::vec2 velocity;

  glm::vec3 color;

  Shader *shader = nullptr;

  Body(float m, float r, const glm::vec2 &pos, const glm::vec2 &vel,
       const glm::vec3 &col)
      : mass(m), radius(r), position(pos), velocity(vel), color(col) {}
};
