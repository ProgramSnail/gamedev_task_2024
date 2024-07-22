#include "Engine.h"
#include <iostream>
#include <memory.h>
#include <stdlib.h>

// #include <stdio.h>

#include "Canvas.hpp"
#include "Map.hpp"
#include "Player.hpp"
#include "Snake.hpp"
#include "Utils.hpp"
#include "World.hpp"

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
void initialize() { srand(time(0)); }

float game_time = 0.0f;

Player player{
    .pos = {.x = 20, .y = 20},
    .direction = {.x = 1.0, .y = 0.0},
};

World world;

Map map{{
    .gen_interval = 1.0,
    .food_exists_gens = 10,
    .gen_food_count = 1000,
    .size = {.x = 20000, .y = 20000},
    .min_food_weight = 1,
    .max_food_weight = 10,
    .food_color = Color::RED,
}};

auto snake = Worm({{.pos = Veci(player.pos), .color = Color::GREEN}, 100, 10});

// this function is called to update game data,
// dt - time elapsed since the previous update (in seconds)
void act(float dt) {
  if (is_key_pressed(VK_ESCAPE))
    schedule_quit_game();

  world.cursor = utils::get_cursor();
  if (world.cursor != world.prev_cursor and utils::is_valid_pos(world.cursor)) {
    Vecf diff(world.cursor - utils::get_center()); // - pos;

    if (diff.len() > MIN_CONTROL_DISTANCE) {
      player.direction = diff.norm();
    }
  }

  int speed = 200;
  player.pos += player.direction * dt * speed;

  game_time += dt;
  world.prev_cursor = world.cursor;

  snake.add(Veci(player.pos));

  snake.inc_length(map.eat(Veci(player.pos), 30));

  map.act(dt);
}

// fill buffer in this function
// uint32_t buffer[SCREEN_HEIGHT][SCREEN_WIDTH] - is an array of 32-bit colors
// (8 bits per R, G, B)
void draw() {
  // clear backbuffer
  memset(buffer, 0, SCREEN_HEIGHT * SCREEN_WIDTH * sizeof(uint32_t));

  Veci map_offset = Veci(player.pos) - utils::get_center();

  snake.draw(map_offset);
  map.draw(map_offset);
  // paint::circle({{.pos = Veci(pos), .color = Color::ORANGE}, 20});
}

// free game data in this function
void finalize() {}
