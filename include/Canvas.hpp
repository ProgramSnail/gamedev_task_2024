#pragma once

#include <cmath>

#include "Engine.h"
#include "Utils.hpp"
#include "Vec.hpp"

using Screen = uint32_t[SCREEN_HEIGHT][SCREEN_WIDTH];

namespace canvas {

struct Object {
  Veci pos;
  Color color;
};

struct Square : public Object {
  int64_t side;
};

struct Circle : public Object {
  int64_t radius;
};

} // namespace canvas

namespace paint {

void square(const canvas::Square &s);

void circle(const canvas::Circle &c);

} // namespace paint
