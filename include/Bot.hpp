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

    if (target_.has_value()) {
      if (target_ != prev_target_) {
        direction_ = (Vecf(target_.value()) - real_pos_).norm();
      }
    } else {
      direction_ = {};
    }

    prev_target_ = target_;
  }

protected:
  const Config bot_config_;

  std::optional<Veci> target_ = {};
  std::optional<Veci> prev_target_ = {};
  float time_from_target_set_ = 0;
};

//

inline Bot::Config default_bot_config = {
    .time_between_targets = 0.5,
};

inline Bot default_bot(Veci pos, Map &map) {
  return Bot(
      {
          .obj =
              {
                  .pos = pos,
                  .color = {color::GRAY},
              },
          .initial_length = 20,
          .radius = 10,
      },
      default_snake_config, default_bot_config, map);
}
