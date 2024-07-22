#pragma once

#include <deque>

#include "Canvas.hpp"
#include "Utils.hpp"
#include "Vec.hpp"

class Map : public GameObject {
  struct Food {
    size_t gen;
    Veci pos;
    int weight;
    bool eaten = false;
  };

public:
  struct Config {
    double gen_interval;
    size_t food_exists_gens;
    size_t gen_food_count;
    Veci size;
    int min_food_weight;
    int max_food_weight;
    Color food_color;
  };

  Map(Config config) : config_(config) {}

  void act(float dt) override {
    time_from_last_gen_ += dt;
    if (time_from_last_gen_ > config_.gen_interval) {
      time_from_last_gen_ -= config_.gen_interval;
      generate();
    }
  }

  int eat(Veci pos, int dist) { // TODO: faster variant ?
    size_t eaten_weight = 0;
    for (auto &food : food_) {
      if ((pos - food.pos).len_sq() < dist * dist and not food.eaten) {
        food.eaten = true;
        eaten_weight += food.weight;
      }
    }
    return eaten_weight;
  }

  void draw(Veci offset) override {
    for (const auto &food : food_) {
      Veci food_pos = food.pos - offset;
      if (utils::is_valid_pos(food_pos) and not food.eaten) {
        paint::circle(
            {{.pos = food_pos, .color = config_.food_color}, food.weight * 3});
      }
    }
  }

private:
  void generate() {
    ++current_gen_;
    while (food_.front().gen + config_.food_exists_gens < current_gen_) {
      food_.pop_front();
    }

    for (size_t i = 0; i < config_.gen_food_count; ++i) {
      food_.push_back({
          .gen = current_gen_,
          .pos = {.x = rand() % config_.size.x, .y = rand() % config_.size.y},
          .weight = config_.min_food_weight +
                    rand() % std::abs(config_.max_food_weight -
                                      config_.min_food_weight),
      });
    }
  }

private:
  Config config_;
  double time_from_last_gen_ = 0;
  size_t current_gen_ = 0;
  std::deque<Food> food_ = {};
};
