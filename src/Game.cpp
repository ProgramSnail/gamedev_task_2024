#include "Engine.h"
#include <iostream>
#include <memory.h>
#include <stdlib.h>

// #include <stdio.h>

#include "Canvas.hpp"

constexpr double MIN_CONTROL_DISTANCE = 10;

//
//  You are free to modify this file
//

//  is_key_pressed(int button_vk_code) - check if a key is pressed,
//                                       use keycodes (VK_SPACE, VK_RIGHT,
//                                       VK_LEFT, VK_UP, VK_DOWN, VK_RETURN)
//
//  get_cursor_x(), get_cursor_y() - get mouse cursor position
//  is_mouse_button_pressed(int button) - check if mouse button is pressed (0 -
//  left button, 1 - right button) schedule_quit_game() - quit game after act()

// initialize game data in this function
void initialize() {}

float game_time = 0.0f;
Vecf pos = {.x = 20, .y = 20};
Vecf direction{.x = 1.0, .y = 0.0};
Veci prev_cursor = {.x = 0, .y = 0};

// this function is called to update game data,
// dt - time elapsed since the previous update (in seconds)
void act(float dt) {
  if (is_key_pressed(VK_ESCAPE))
    schedule_quit_game();

  Veci cursor = get_cursor();
  if (cursor != prev_cursor and is_valid_pos(cursor)) {
    Vecf diff = Vecf(cursor) - pos;

    if (diff.len() > MIN_CONTROL_DISTANCE) {
      direction = diff.norm();
    }
  }

  int speed = 200;
  pos += direction * dt * speed;

  game_time += dt;
  prev_cursor = cursor;
  // std::cout << "pos: " << pos.x << ' ' << pos.y << std::endl;
  // std::cout << "curs: " << get_cursor().x << ' ' << get_cursor().y <<
  // std::endl;
}

// fill buffer in this function
// uint32_t buffer[SCREEN_HEIGHT][SCREEN_WIDTH] - is an array of 32-bit colors
// (8 bits per R, G, B)
void draw() {
  // clear backbuffer
  memset(buffer, 0, SCREEN_HEIGHT * SCREEN_WIDTH * sizeof(uint32_t));

  Circle sq({.pos = Veci(pos), .size = 20});
  sq.show();
}

// free game data in this function
void finalize() {}
