#pragma once

#include <deque>

#include "Canvas.hpp"
#include "Map.hpp"

namespace canvas {

class SnakeObject {
public:
  struct Config {
    Object obj;
    uint initial_length;
    int radius;
  };

  SnakeObject(Config config)
      : canvas_config_(config), length_{config.initial_length},
        track_{config.obj.pos} {}

  void add(Veci pos);

  void draw(Veci offset = {}) const;

  //

  Veci get_pos() {
    if (track_.empty()) {
      throw std::exception();
    }
    return track_.back();
  }

  //

  uint get_length() { return length_; }

  uint get_initial_length() { return canvas_config_.initial_length; }

  void set_length(uint length) { length_ = length; }

  void inc_length(int inc) {
    if (-inc > int(length_)) {
      length_ = 1;
    } else {
      length_ += inc;
    }
  }

  //

  bool touches(const SnakeObject &other);

protected:
  const Config canvas_config_;

  size_t length_;
  std::deque<Veci> track_;
};

} // namespace canvas

class Snake : public canvas::SnakeObject, public GameObject {
public:
  struct Config {
    double speed;
    float move_interval;
  };

  Snake(canvas::SnakeObject::Config canvas_config, Config snake_config,
        Map &map)
      : SnakeObject(canvas_config), snake_config_(snake_config), map_(map),
        real_pos_(canvas_config.obj.pos) {}

  void act(float dt) override {
    int eaten = map_.eat(utils::to_world_coord(get_pos()), 20);
    inc_length(eaten);

    change_direction(dt);

    move(dt);
  }

  void draw(Veci offset) override { SnakeObject::draw(offset); }

protected:
  virtual void change_direction(float dt) = 0;

  virtual void move(float dt);

protected:
  const Config snake_config_;
  Map &map_;

  Vecf real_pos_;
  Vecf direction_ = {};
  float move_time_delta_ = 0;
};
