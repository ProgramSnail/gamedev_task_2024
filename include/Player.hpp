#pragma once

#include "Vec.hpp"

struct Player {
  Vecf pos;
  Vecf direction;
  double speed;
  double move_interval;
  double move_time_delta;
};
