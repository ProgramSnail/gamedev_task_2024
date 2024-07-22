#pragma once

#include <algorithm>

#include "Engine.h"
#include "Vec.hpp"

namespace utils {

namespace safe {

inline int lx(int x) { return std::max(0, x); }

inline int ly(int y) { return std::max(0, y); }

inline int ux(int x) { return std::min(SCREEN_HEIGHT - 1, x); }

inline int uy(int y) { return std::min(SCREEN_WIDTH - 1, y); }

inline int x(int x) { return safe::ux(safe::lx(x)); }
inline int y(int y) { return safe::uy(safe::ly(y)); }
} // namespace safe

inline uint32_t *screen_at(int x, int y) {
  return &buffer[safe::x(x)][safe::y(y)];
}

template <typename T> inline bool is_valid_pos(Vec<T> pos) {
  return pos.x >= 0 and pos.x < SCREEN_HEIGHT and pos.y >= 0 and
         pos.y < SCREEN_WIDTH;
}

inline Veci get_cursor() { return {.x = get_cursor_y(), .y = get_cursor_x()}; }

inline constexpr Veci get_center() {
  return {.x = SCREEN_HEIGHT / 2, .y = SCREEN_WIDTH / 2};
}

} // namespace utils

namespace color {

enum FixedColor : uint32_t {
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
constexpr FixedColor BG = BLACK;

struct Color {
  uint32_t v;
};

inline Color scale(Color color, double scale) {
  static constexpr uint32_t COL_BITS = 8;
  static constexpr uint32_t COMPONENTS = 4;
  for (uint32_t i = COL_BITS; i < COMPONENTS * COL_BITS; i += COL_BITS) {
    uint32_t comp = (color.v >> i) % (1 << COL_BITS);
    color.v -= (comp << i);
    color.v += (uint32_t(comp * scale) << i);
  }
  return color;
}

} // namespace color
using color::Color;

//

class GameObject {
public:
  virtual void act(float dt) = 0;
  virtual void draw(Veci offset) = 0;

  virtual ~GameObject() {}
};
