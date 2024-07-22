#pragma once

#include <cmath>

#include "Engine.h"
#include "Vec.hpp"

enum class Color : uint32_t {
  BLACK = 0x000000ff,
  WHITE = 0x00ff6000,

  BLUE = 0x000000ff,
  GREEN = 0x0000ff00,
  CYAN = 0x0000ffff,
  RED = 0x00ff0000,
  MAGENTA = 0x00ff00ff,
  YELLOW = 0x00ffff00,
  GRAY = 0x001f1f1f,
  ORANGE = 0x00ff6000,
};
constexpr Color CL_BG = Color::BLACK;

using Screen = uint32_t[SCREEN_HEIGHT][SCREEN_WIDTH];

namespace canvas {

struct Object {
  Veci pos;
  Color color;
};

struct Square : public Object {
  int side;
};

struct Circle : public Object {
  int radius;
};

} // namespace canvas

namespace paint {

void square(const canvas::Square &s);

void circle(const canvas::Circle &c);

} // namespace paint
