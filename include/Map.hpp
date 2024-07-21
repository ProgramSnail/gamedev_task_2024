#pragma once

#include <deque>

#include "Utils.hpp"
#include "Vec.hpp"

class Map : public GameObject {
  struct Food {
    size_t gen;
    Veci pos;
    int weight;
    bool eaten = false;
  };

  static constexpr double GEN_INTERVAL = 1.0;
  static constexpr size_t FOOD_EXISTS_GENS = 10;
  static constexpr size_t GEN_FOOD_COUNT = 1000;
  static constexpr int SIZE_X = 20000;
  static constexpr int SIZE_Y = 20000;

public:
  void act(float dt) override {
    time_from_last_gen_ += dt;
    if (time_from_last_gen_ > GEN_INTERVAL) {
      time_from_last_gen_ -= GEN_INTERVAL;
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

  void draw() override {} // TODO

private:
  void generate() {
    ++current_gen_;
    while (food_.front().gen + FOOD_EXISTS_GENS < current_gen_) {
      food_.pop_front();
    }

    for (size_t i = 0; i < GEN_FOOD_COUNT; ++i) {
      food_.push_back({.gen = current_gen_,
                       .pos = {.x = rand() % SIZE_X, .y = rand() % SIZE_Y},
                       .weight = 1});
    }
  }

private:
  double time_from_last_gen_ = 0;
  size_t current_gen_ = 0;
  std::deque<Food> food_ = {};
};
