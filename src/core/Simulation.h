#pragma once
#include "Body.h"
#include "Config.h"
#include <vector>

class Simulation {
public:
  Simulation();

  void Reset(const Config &config);
  void Update(float dt, const Config &config);

  std::vector<Body> &GetBodies() { return bodies; }
  const std::vector<Body> &GetBodies() const { return bodies; }

  void AddBody(const Body &body);
  void ClearBodies();

  void SetWorldBounds(float width, float height);

  float GetTotalEnergy() const;
  glm::vec2 GetTotalMomentum() const;

private:
  void HandleWallCollision(Body &body, const Config &config);
  std::vector<Body> bodies;

  void ResolveCollision(Body &a, Body &b, const Config &config);
  void PositionalCorrection(Body &a, Body &b);

  float worldLeft;
  float worldRight;
  float worldTop;
  float worldBottom;
};
