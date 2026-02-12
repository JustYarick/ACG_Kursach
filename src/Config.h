#pragma once
#include <glm/glm.hpp>

struct Config {
  float restitution = 1.0f;

  bool simulationRunning = false;

  float clearColor[3] = {0.1f, 0.2f, 0.3f};
};
