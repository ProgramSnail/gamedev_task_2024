#include "Snake.hpp"

void Worm::add(Veci pos) {
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
