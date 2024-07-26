#pragma once

#include <optional>

#include "Map.hpp"
#include "Snake.hpp"

class Bot : public Snake {
public:
  struct Config {
    float time_between_targets;
  };

  Bot(canvas::SnakeObject::Config canvas_config, Snake::Config snake_config,
      Config bot_config, Map &map)
      : Snake(canvas_config, snake_config, map), bot_config_(bot_config) {}

protected:
  void change_direction(float dt) override {
    time_from_target_set_ += dt;

    if (not target_.has_value() or
        time_from_target_set_ >= bot_config_.time_between_targets or
        (target_.value() - get_pos()).len_sq() <
            canvas_config_.radius * canvas_config_.radius) {
      time_from_target_set_ = 0;

      target_ = map_.find_nearest_food(get_pos());
    }

    // check for case when no food found
    if (target_.has_value()) {
      direction_ = (Vecf(target_.value()) - real_pos_).norm();
      // TODO: manually change direction
    }
  }

protected:
  const Config bot_config_;

  std::optional<Veci> target_ = {};
  float time_from_target_set_ = 0;
};
