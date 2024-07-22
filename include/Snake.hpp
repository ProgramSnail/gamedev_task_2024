#pragma once

#include <deque>

#include "Canvas.hpp"

namespace canvas {

struct WormObject : public Object {
  size_t length;
  int radius;
};

} // namespace canvas

class Worm : protected canvas::WormObject {
public:
  Worm(canvas::WormObject obj) : WormObject(obj), track_{pos} {}

  void add(Veci pos);

  void draw(Veci offset = {}) const;

  size_t get_length() { return length; }

  void set_length(size_t length) { this->length = length; }

  void inc_length(int inc) {
    if (-inc > static_cast<int>(length)) {
      length = 0;
    } else {
      length += inc;
    }
  }

protected:
  std::deque<Veci> track_;
};
