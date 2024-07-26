#include "Snake.hpp"

namespace canvas {

void SnakeObject::add(Veci pos) {
  track_.push_back(pos);
  if (track_.size() > length_) {
    track_.pop_front();
  }
}

void SnakeObject::draw(Veci offset) const {
  for (const auto &pos : track_) {
    paint::circle({{.pos = pos - offset, .color = canvas_config_.obj.color},
                   canvas_config_.radius});
  }
}

bool SnakeObject::touches(const SnakeObject &other) {
  int dist = canvas_config_.radius + other.canvas_config_.radius;
  for (const auto &elem : other.track_) {
    if ((get_pos() - elem).len_sq() < dist * dist) {
      return true;
    }
  }
  return false;
}

} // namespace canvas

void Snake::move(float dt) {
  real_pos_ += direction_ * dt * snake_config_.speed;
  move_time_delta_ += dt;
  if (move_time_delta_ > snake_config_.move_interval) {
    move_time_delta_ -= snake_config_.move_interval;
    add(Veci(real_pos_));
  }
}
