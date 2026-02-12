#include "Physics.h"
#include <glm/glm.hpp>

void Physics::ResolveCollision(Body &b1, Body &b2, const Config &config) {
  glm::vec2 normal = b2.position - b1.position;
  float distance = glm::length(normal);

  if (distance == 0.0f)
    return;

  normal = glm::normalize(normal);

  glm::vec2 relativeVelocity = b2.velocity - b1.velocity;

  float velAlongNormal = glm::dot(relativeVelocity, normal);

  if (velAlongNormal > 0)
    return;

  float e = config.restitution;

  float invMass1 = 1.0f / b1.mass;
  float invMass2 = 1.0f / b2.mass;

  float j = -(1 + e) * velAlongNormal;
  j /= (invMass1 + invMass2);

  glm::vec2 impulse = j * normal;

  b1.velocity -= invMass1 * impulse;
  b2.velocity += invMass2 * impulse;
}
