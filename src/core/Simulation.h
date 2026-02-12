#pragma once
#include "Body.h"
#include "../Config.h"

class Simulation {
public:
  Simulation();

  void Reset(const Config &config);
  void Update(float dt, const Config &config);

  Body &GetBody1() { return body1; }
  Body &GetBody2() { return body2; }

  void SetWorldBounds(float width, float height);

  float GetTotalEnergy() const;
  glm::vec2 GetTotalMomentum() const;

private:
  void ResolveCollision(const Config &config);
  void HandleWallCollision(Body &body, const Config &config);
  void PositionalCorrection();

  float worldLeft = -1.0f;
  float worldRight = 1.0f;
  float worldTop = 1.0f;
  float worldBottom = -1.0f;

  Body body1;
  Body body2;
};
