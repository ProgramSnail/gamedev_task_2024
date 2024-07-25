#pragma once

#include <optional>

#include "Map.hpp"
#include "Snake.hpp"

class Bot : public Snake, public GameObject {
public:
  struct Config {
    float time_between_targets;
    double speed;
    float move_interval;
  };

  Bot(canvas::SnakeObject obj, Config config, Map &map)
      : Snake(obj), config_(config), map_(map), real_pos_(obj.pos) {}

  void act(float dt) override {
    time_from_target_set_ += dt;

    int eaten = map_.eat(utils::to_world_coord(pos), 20);
    inc_length(eaten);

    if (not target_.has_value() or
        time_from_target_set_ >= config_.time_between_targets or
        (target_.value() - pos).len_sq() < radius * radius) {
      time_from_target_set_ = 0;

      target_ = map_.find_nearest_food(pos);
    }

    // check for case when no food found
    if (target_.has_value()) {
      direction_ = (Vecf(target_.value()) - real_pos_).norm();
      // TODO: manually change direction
    }

    move(dt);
  }

  void draw(Veci offset) override { Snake::draw(offset); }

protected:
  void move(float dt) {
    real_pos_ += direction_ * dt * config_.speed;
    move_time_delta_ += dt;
    if (move_time_delta_ > config_.move_interval) {
      move_time_delta_ -= config_.move_interval;
      add(Veci(real_pos_));
    }
  }

private:
  const Config config_;
  Map &map_;

  Vecf real_pos_;
  Vecf direction_ = {};
  std::optional<Veci> target_ = {};
  float time_from_target_set_ = 0;
  float move_time_delta_ = 0;
};
