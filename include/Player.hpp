#pragma once

#include "Snake.hpp"

// struct Player {
//   Vecf pos;
//   Vecf direction;
//   double speed;
//   double move_interval;
//   double move_time_delta;
// };

class Player : public Snake {
public:
  using Snake::Snake;

  uint get_score() { return get_length() - get_initial_length(); }

  void act(float dt) override {
    int eaten = map_.eat(
        utils::to_world_coord(get_pos() + utils::get_screen_center()), 20);
    inc_length(eaten);

    change_direction(dt);

    move(dt);
  }

  void draw(Veci offset) const override {
    Snake::draw(offset - utils::get_screen_center());
  }

  bool touches(const SnakeObject &other, Veci offset = {}) override {
    return Snake::touches(other, offset - utils::get_screen_center());
  }

protected:
  void change_direction(float) override {
    Veci cursor = utils::get_cursor();

    if (cursor != prev_cursor_ and utils::is_on_screen(cursor)) {
      Vecf diff(cursor - utils::get_screen_center()); // - pos;

      if (diff.len() > MIN_CONTROL_DISTANCE) {
        direction_ = diff.norm();
      }
    }

    prev_cursor_ = cursor;
  }

protected:
  Veci prev_cursor_ = {};
};
