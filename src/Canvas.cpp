#include "Canvas.hpp"

#include "Utils.hpp"

using namespace utils;

namespace paint {

void square(const canvas::Square &s) {
  for (int x = s.pos.x; x < s.pos.x + s.side; ++x) {
    std::fill(screen_at(x, s.pos.y), screen_at(x, s.pos.y + s.side), s.color.v);
  }
}

void circle(const canvas::Circle &c) {
  for (int x = -c.radius; x < c.radius; ++x) {
    int size_y = std::sqrt(c.radius * c.radius - std::abs(x) * std::abs(x));
    std::fill(screen_at(c.pos.x + x, c.pos.y - size_y),
              screen_at(c.pos.x + x, c.pos.y + size_y), c.color.v);
  }
}

} // namespace paint
