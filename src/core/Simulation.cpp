#include "Simulation.h"
#include <glm/glm.hpp>
#define GLM_ENABLE_EXPERIMENTAL
#include <glm/gtx/norm.hpp>

Simulation::Simulation() {
  body1.radius = 0.2f;
  body2.radius = 0.2f;
}

void Simulation::Reset(const Config &config) {
  body1.mass = config.mass1;
  body2.mass = config.mass2;

  body1.position = config.position1;
  body2.position = config.position2;

  body1.velocity = config.velocity1;
  body2.velocity = config.velocity2;

  body1.radius = 0.2f;
  body2.radius = 0.2f;
}

void Simulation::HandleWallCollision(Body &body, const Config &config) {
  float e = config.restitution;

  // Левая / правая стена
  if (body.position.x - body.radius < -1.0f) {
    body.position.x = -1.0f + body.radius;
    body.velocity.x = -body.velocity.x * e;
  } else if (body.position.x + body.radius > 1.0f) {
    body.position.x = 1.0f - body.radius;
    body.velocity.x = -body.velocity.x * e;
  }

  // Нижняя / верхняя стена
  if (body.position.y - body.radius < -1.0f) {
    body.position.y = -1.0f + body.radius;
    body.velocity.y = -body.velocity.y * e;
  } else if (body.position.y + body.radius > 1.0f) {
    body.position.y = 1.0f - body.radius;
    body.velocity.y = -body.velocity.y * e;
  }
}

void Simulation::Update(float dt, const Config &config) {
  body1.position += body1.velocity * dt;
  body2.position += body2.velocity * dt;

  HandleWallCollision(body1, config);
  HandleWallCollision(body2, config);
  float distance = glm::length(body2.position - body1.position);

  if (distance < body1.radius + body2.radius) {
    ResolveCollision(config);
    PositionalCorrection();
  }
}

void Simulation::SetWorldBounds(float width, float height) {
  float aspect = width / height;

  worldLeft = -aspect;
  worldRight = aspect;
  worldBottom = -1.0f;
  worldTop = 1.0f;
}

void Simulation::ResolveCollision(const Config &config) {
  glm::vec2 normal = body2.position - body1.position;
  float distance = glm::length(normal);

  if (distance == 0.0f)
    return;

  normal = glm::normalize(normal);

  glm::vec2 relativeVelocity = body2.velocity - body1.velocity;
  float velAlongNormal = glm::dot(relativeVelocity, normal);

  if (velAlongNormal > 0)
    return;

  float e = config.restitution;

  float invMass1 = 1.0f / body1.mass;
  float invMass2 = 1.0f / body2.mass;

  float j = -(1 + e) * velAlongNormal;
  j /= (invMass1 + invMass2);

  glm::vec2 impulse = j * normal;

  body1.velocity -= invMass1 * impulse;
  body2.velocity += invMass2 * impulse;
}

void Simulation::PositionalCorrection() {
  glm::vec2 normal = body2.position - body1.position;
  float distance = glm::length(normal);

  if (distance == 0.0f)
    return;

  float penetration = body1.radius + body2.radius - distance;
  if (penetration <= 0.0f)
    return;

  normal = glm::normalize(normal);

  glm::vec2 correction = normal * penetration * 0.5f;
  body1.position -= correction;
  body2.position += correction;
}

float Simulation::GetTotalEnergy() const {
  float e1 = 0.5f * body1.mass * glm::length2(body1.velocity);
  float e2 = 0.5f * body2.mass * glm::length2(body2.velocity);
  return e1 + e2;
}

glm::vec2 Simulation::GetTotalMomentum() const {
  return body1.mass * body1.velocity + body2.mass * body2.velocity;
}
