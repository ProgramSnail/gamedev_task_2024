#pragma once

#include <deque>

#include "Canvas.hpp"

namespace canvas {

struct SnakeObject : public Object {
  size_t length;
  int radius;
};

} // namespace canvas

class Snake : protected canvas::SnakeObject {
public:
  Snake(canvas::SnakeObject obj) : SnakeObject(obj), track_{pos} {}

  void add(Veci pos);

  void draw(Veci offset = {}) const;

  //

  Veci get_pos() { return pos; }

  //

  size_t get_length() { return length; }

  void set_length(size_t length) { this->length = length; }

  void inc_length(int inc) {
    if (-inc > static_cast<int>(length)) {
      length = 0;
    } else {
      length += inc;
    }
  }

  //

  bool touches(const Snake &other);

protected:
  std::deque<Veci> track_;
};
