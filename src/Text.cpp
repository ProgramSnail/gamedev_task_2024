#include "Text.hpp"

#include <string>

using utils::screen_at;

constexpr uint LETTER_WIDTH = 4;
constexpr uint LETTER_HEIGHT = 6;

using Letter = bool[LETTER_WIDTH][LETTER_HEIGHT];

namespace utils {

constexpr Letter letter_0 = {
    {1, 1, 1, 1, 1},
    {1, 0, 0, 0, 1},
    {1, 0, 0, 0, 1},
    {1, 1, 1, 1, 1},
};

constexpr Letter letter_1 = {
    {0, 0, 0, 0, 0},
    {0, 0, 0, 0, 0},
    {0, 0, 0, 0, 0},
    {1, 1, 1, 1, 1},
};

constexpr Letter letter_2 = {
    {1, 0, 1, 1, 1},
    {1, 0, 1, 0, 1},
    {1, 0, 1, 0, 1},
    {1, 1, 1, 0, 1},
};

constexpr Letter letter_3 = {
    {1, 0, 1, 0, 1},
    {1, 0, 1, 0, 1},
    {1, 0, 1, 0, 1},
    {1, 1, 1, 1, 1},
};

constexpr Letter letter_4 = {
    {1, 1, 1, 0, 0},
    {0, 0, 1, 0, 0},
    {0, 0, 1, 0, 0},
    {1, 1, 1, 1, 1},
};

constexpr Letter letter_5 = {
    {1, 1, 1, 0, 1},
    {1, 0, 1, 0, 1},
    {1, 0, 1, 0, 1},
    {1, 0, 1, 1, 1},
};

constexpr Letter letter_6 = {
    {1, 1, 1, 1, 1},
    {1, 0, 1, 0, 1},
    {1, 0, 1, 0, 1},
    {1, 0, 1, 1, 1},
};

constexpr Letter letter_7 = {
    {1, 0, 0, 0, 0},
    {1, 0, 0, 0, 0},
    {1, 0, 0, 0, 0},
    {1, 1, 1, 1, 1},
};

constexpr Letter letter_8 = {
    {1, 1, 1, 1, 1},
    {1, 0, 1, 0, 1},
    {1, 0, 1, 0, 1},
    {1, 1, 1, 1, 1},
};

constexpr Letter letter_9 = {
    {1, 1, 1, 0, 1},
    {1, 0, 1, 0, 1},
    {1, 0, 1, 0, 1},
    {1, 1, 1, 1, 1},
};

constexpr Letter letter_undef = {
    {0, 0, 0, 0, 0},
    {0, 0, 0, 0, 0},
    {0, 0, 0, 0, 0},
    {0, 0, 0, 0, 0},
};

} // namespace utils

namespace paint {

void text(const canvas::Text &t) {
  std::string value_str = std::to_string(t.value);
  size_t offset = 0;
  for (const auto &ch : value_str) {
    const Letter *letter = nullptr;
    switch (ch) {
    case '0':
      letter = &utils::letter_0;
      break;
    case '1':
      letter = &utils::letter_1;
      break;
    case '2':
      letter = &utils::letter_2;
      break;
    case '3':
      letter = &utils::letter_3;
      break;
    case '4':
      letter = &utils::letter_4;
      break;
    case '5':
      letter = &utils::letter_5;
      break;
    case '6':
      letter = &utils::letter_6;
      break;
    case '7':
      letter = &utils::letter_7;
      break;
    case '8':
      letter = &utils::letter_8;
      break;
    case '9':
      letter = &utils::letter_9;
      break;
    default:
      letter = &utils::letter_undef;
      break;
    }

    for (uint i = 0; i < LETTER_WIDTH; ++i) {
      for (uint j = 0; j < LETTER_HEIGHT; ++j) {
        if ((*letter)[i][j]) {
          for (uint k = 0; k < t.scale; ++k) {
            int pixel_offset_y =
                i * t.scale + offset * (LETTER_WIDTH + 1) * t.scale;
            int pixel_offset_x = j * t.scale + k;
            std::fill(screen_at({
                          .x = t.pos.x + pixel_offset_x,
                          .y = t.pos.y + pixel_offset_y,
                      }),
                      screen_at({
                          .x = t.pos.x + pixel_offset_x,
                          .y = t.pos.y + pixel_offset_y + int(t.scale),
                      }),
                      t.color.v);
          }
        }
      }
    }

    ++offset;
  }
}

} // namespace paint
