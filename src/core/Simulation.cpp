#include "Simulation.h"
#define GLM_ENABLE_EXPERIMENTAL
#include <glm/glm.hpp>
#include <glm/gtx/norm.hpp>
#include <algorithm>

Simulation::Simulation() {
  worldLeft = -1.0f;
  worldRight = 1.0f;
  worldBottom = -1.0f;
  worldTop = 1.0f;
}

void Simulation::Reset(const Config &) {
  // Reset только очищает состояние
  bodies.clear();
}

void Simulation::AddBody(const Body &body) { bodies.push_back(body); }

void Simulation::ClearBodies() { bodies.clear(); }

void Simulation::Update(float dt, const Config &config) {
  // Интеграция движения
  for (auto &body : bodies) {
    body.position += body.velocity * dt;
    HandleWallCollision(body, config);
  }

  // Проверка столкновений (O(n²))
  const size_t count = bodies.size();

  for (size_t i = 0; i < count; ++i) {
    for (size_t j = i + 1; j < count; ++j) {
      Body &a = bodies[i];
      Body &b = bodies[j];

      float distance = glm::length(b.position - a.position);

      if (distance < a.radius + b.radius) {
        ResolveCollision(a, b, config);
        PositionalCorrection(a, b);
      }
    }
  }
}

void Simulation::HandleWallCollision(Body &body, const Config &config) {
  const float e = config.restitution;

  // X-границы
  if (body.position.x - body.radius < worldLeft) {
    body.position.x = worldLeft + body.radius;
    body.velocity.x *= -e;
  } else if (body.position.x + body.radius > worldRight) {
    body.position.x = worldRight - body.radius;
    body.velocity.x *= -e;
  }

  // Y-границы
  if (body.position.y - body.radius < worldBottom) {
    body.position.y = worldBottom + body.radius;
    body.velocity.y *= -e;
  } else if (body.position.y + body.radius > worldTop) {
    body.position.y = worldTop - body.radius;
    body.velocity.y *= -e;
  }
}

void Simulation::ResolveCollision(Body &a, Body &b, const Config &config) {
  glm::vec2 normal = b.position - a.position;
  float distance = glm::length(normal);

  if (distance == 0.0f)
    return;

  normal /= distance;

  glm::vec2 relativeVelocity = b.velocity - a.velocity;
  float velAlongNormal = glm::dot(relativeVelocity, normal);

  if (velAlongNormal > 0.0f)
    return;

  const float e = config.restitution;

  float invMassA = 1.0f / a.mass;
  float invMassB = 1.0f / b.mass;

  float j = -(1.0f + e) * velAlongNormal;
  j /= (invMassA + invMassB);

  glm::vec2 impulse = j * normal;

  a.velocity -= invMassA * impulse;
  b.velocity += invMassB * impulse;
}

void Simulation::PositionalCorrection(Body &a, Body &b) {
  glm::vec2 normal = b.position - a.position;
  float distance = glm::length(normal);

  if (distance == 0.0f)
    return;

  float penetration = a.radius + b.radius - distance;
  if (penetration <= 0.0f)
    return;

  normal /= distance;

  const float percent = 0.8f; // степень коррекции
  const float slop = 0.01f;   // допустимая погрешность

  float invMassA = 1.0f / a.mass;
  float invMassB = 1.0f / b.mass;

  glm::vec2 correction = normal * percent * std::max(penetration - slop, 0.0f) /
                         (invMassA + invMassB);

  a.position -= invMassA * correction;
  b.position += invMassB * correction;
}

void Simulation::SetWorldBounds(float width, float height) {
  float aspect = width / height;

  worldLeft = -aspect;
  worldRight = aspect;
  worldBottom = -1.0f;
  worldTop = 1.0f;
}

float Simulation::GetTotalEnergy() const {
  float total = 0.0f;

  for (const auto &body : bodies)
    total += 0.5f * body.mass * glm::length2(body.velocity);

  return total;
}

glm::vec2 Simulation::GetTotalMomentum() const {
  glm::vec2 total(0.0f);

  for (const auto &body : bodies)
    total += body.mass * body.velocity;

  return total;
}
