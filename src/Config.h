#pragma once

struct Config {
  // Тип удара
  float restitution = 1.0f; // 0..1

  // Массы
  float mass1 = 1.0f;
  float mass2 = 1.0f;

  // Начальные скорости
  float velocity1 = 1.0f;
  float velocity2 = -1.0f;

  // Режим
  bool is3D = false;
  bool simulationRunning = false;

  // Визуал
  float clearColor[3] = {0.1f, 0.2f, 0.3f};
};
