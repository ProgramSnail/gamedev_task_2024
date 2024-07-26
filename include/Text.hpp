#pragma once

#include "Canvas.hpp"

namespace canvas {

struct Text : public Object {
  uint scale;
  uint value;
};

} // namespace canvas

namespace paint {

void text(const canvas::Text &t);

} // namespace paint
