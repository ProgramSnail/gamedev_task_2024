#pragma once

#include <algorithm>
#include <cmath>
#include <vector>
#

#include "Engine.h"
#include "Utils.hpp"

enum class Color : uint32_t {
  BLACK = 0x000000ff,
  WHITE = 0x00ff6000,

  BLUE = 0x000000ff,
  GREEN = 0x0000ff00,
  CYAN = 0x0000ffff,
  RED = 0x00ff0000,
  MAGENTA = 0x00ff00ff,
  YELLOW = 0x00ffff00,
  GRAY = 0x001f1f1f,
  ORANGE = 0x00ff6000,
};
constexpr Color CL_BG = Color::BLACK;

using Screen = uint32_t[SCREEN_HEIGHT][SCREEN_WIDTH];

class CanvasObject {
public:
  struct Config {
    Veci pos;
    int size;
    Color color = Color ::WHITE;
  };
  CanvasObject(Config config)
      : pos_(config.pos), size_(config.size), color_(config.color),
        shown_(false) {}

  virtual void move_to(Veci) = 0;
  virtual void show() = 0;
  virtual void hide() = 0;

  virtual ~CanvasObject() {
    if (shown_) {
      // hide(); // TODO
    }
  }

protected:
  Veci pos_;
  int size_;
  Color color_;
  bool shown_;
};

class StatelessCanvasObject : public CanvasObject {
public:
  using CanvasObject::CanvasObject;

  void move_to(Veci pos) override {
    if (not shown_) {
      return;
    }
    hide();
    pos_ = pos;
    show();
  }

  void show() override { fill(color_); }

  void hide() override { fill(CL_BG); }

protected:
  virtual void fill(Color color) = 0;
};

class Square : public StatelessCanvasObject {
public:
  using StatelessCanvasObject::StatelessCanvasObject;

protected:
  void fill(Color color) override {
    for (int x = pos_.x; x < pos_.x + size_; ++x) {
      std::fill(screen_at(x, pos_.y), screen_at(x, pos_.y + size_),
                static_cast<uint32_t>(color));
    }
  }
};

class Circle : public StatelessCanvasObject {
public:
  using StatelessCanvasObject::StatelessCanvasObject;

protected:
  void fill(Color color) override {
    for (int x = -size_; x < size_; ++x) {
      int size_y = std::sqrt(size_ * size_ - std::abs(x) * std::abs(x));
      std::fill(screen_at(pos_.x + x, pos_.y - size_y),
                screen_at(pos_.x + x, pos_.y + size_y),
                static_cast<uint32_t>(color));
    }
  }
};

class Worm : public CanvasObject {
  Worm(CanvasObject::Config config, size_t max_track_size)
      : CanvasObject(config), max_track_size_(max_track_size) {}

protected:
  const size_t max_track_size_;
  std::vector<Circle> track_;
};

// class Canvas {
// public:
//   Canvas(Screen &screen) : screen_(screen) {}

//   size_t insert(CanvasObject obj) {}
//   void erase(size_t id) {}

// private:
//   Screen &screen_;
// };
