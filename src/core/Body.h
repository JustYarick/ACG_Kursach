#pragma once
#include <glm/glm.hpp>

struct Body {
  float mass;
  float radius;

  glm::vec2 position;
  glm::vec2 velocity;
};
