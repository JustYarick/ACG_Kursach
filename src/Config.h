#pragma once
#include <glm/glm.hpp>

struct Config {

  float restitution = 1.0f;

  float mass1 = 1.0f;
  float mass2 = 1.0f;

  glm::vec2 velocity1 = {1.0f, 0.0f};
  glm::vec2 velocity2 = {-1.0f, 0.0f};

  glm::vec2 position1 = {-0.5f, 0.0f};
  glm::vec2 position2 = {0.5f, 0.0f};

  bool simulationRunning = false;

  float clearColor[3] = {0.1f, 0.2f, 0.3f};
};
