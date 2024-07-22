#include "Engine.h"
#include <ctime>
#include <memory.h>
#include <stdlib.h>

// #include <stdio.h>

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
void initialize() { std::srand(std::time(0)); }

float game_time = 0.0f;

Player player{
    .pos = {.x = 20, .y = 20},
    .direction = {.x = 1.0, .y = 0.0},
    .speed = 200.0,
    .move_interval = 0.01,
    .move_time_delta = 0,
};

World world;

Map map{{
    .gen_interval = 1.0,
    .food_exists_gens = 10,
    .gen_food_count = 1000,
    .size = {.x = 20000, .y = 20000},
    .min_food_weight = 1,
    .max_food_weight = 5,
    .food_color = {color::RED},
}};

// std::vector<Worm> bots; // TODO

auto snake = Worm(canvas::WormObject{
    {.pos = Veci(player.pos), .color = {color::GREEN}},
    10,
    10,
});

// this function is called to update game data,
// dt - time elapsed since the previous update (in seconds)
void act(float dt) {
  if (is_key_pressed(VK_ESCAPE)) {
    schedule_quit_game();
  }

  map.act(dt);

  world.cursor = utils::get_cursor();
  if (world.cursor != world.prev_cursor and utils::is_valid_pos(world.cursor)) {
    Vecf diff(world.cursor - utils::get_center()); // - pos;

    if (diff.len() > MIN_CONTROL_DISTANCE) {
      player.direction = diff.norm();
    }
  }

  player.pos += player.direction * dt * player.speed;

  game_time += dt;
  world.prev_cursor = world.cursor;

  player.move_time_delta += dt;
  if (player.move_time_delta > player.move_interval) {
    player.move_time_delta -= player.move_interval;
    snake.add(Veci(player.pos));
  }

  int eaten = map.eat(Veci(player.pos), 20);
  snake.inc_length(eaten);

  // TODO
  // for (const auto &bot : bots) {
  //   if (snake.touches(bot)) { // GAME OVER
  //     schedule_quit_game();
  //   }
  //   if (bot.touches(snake)) {
  //     // regen bot
  //   }
  // }
}

// fill buffer in this function
// uint32_t buffer[SCREEN_HEIGHT][SCREEN_WIDTH] - is an array of 32-bit colors
// (8 bits per R, G, B)
void draw() {
  // clear backbuffer
  memset(buffer, 0, SCREEN_HEIGHT * SCREEN_WIDTH * sizeof(uint32_t));

  Veci map_offset = Veci(/*player.pos*/ snake.get_pos()) - utils::get_center();

  snake.draw(map_offset);
  map.draw(map_offset);
}

// free game data in this function
void finalize() {}
