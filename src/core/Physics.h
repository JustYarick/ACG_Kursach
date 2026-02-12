#pragma once
#include "Body.h"
#include "../Config.h"

class Physics {
public:
  static void ResolveCollision(Body &b1, Body &b2, const Config &config);
};
