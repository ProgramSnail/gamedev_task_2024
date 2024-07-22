#pragma once

#include "Vec.hpp"

struct World {
  float game_time = {};
  Veci prev_cursor = {};
  Veci cursor = {};
};
