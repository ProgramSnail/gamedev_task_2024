#include "Snake.hpp"

void Snake::add(Veci pos) {
  this->pos = pos;
  track_.push_back(pos);
  if (track_.size() > length) {
    track_.pop_front();
  }
}

void Snake::draw(Veci offset) const {
  for (const auto &pos : track_) {
    paint::circle({{.pos = pos - offset, .color = color}, radius});
  }
}

bool Snake::touches(const Snake &other) {
  int dist = radius + other.radius;
  for (const auto &elem : other.track_) {
    if ((pos - elem).len_sq() < dist * dist) {
      return true;
    }
  }
  return false;
}
