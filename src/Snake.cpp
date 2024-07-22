#include "Snake.hpp"

void Worm::add(Veci pos) {
  this->pos = pos;
  track_.push_back(pos);
  if (track_.size() > length) {
    track_.pop_front();
  }
}

void Worm::draw(Veci offset) const {
  for (const auto &pos : track_) {
    paint::circle({{.pos = pos - offset, .color = color}, radius});
  }
}

bool Worm::touches(const Worm &other) {
  int dist = radius + other.radius;
  for (const auto &elem : other.track_) {
    if ((pos - elem).len_sq() < dist * dist) {
      return true;
    }
  }
  return false;
}
