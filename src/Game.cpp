#include "Engine.h"
#include <ctime>
#include <memory.h>
#include <stdlib.h>

// #include <stdio.h>

#include "Map.hpp"
#include "Params.hpp"
#include "Player.hpp"
#include "Snake.hpp"
#include "Utils.hpp"
#include "World.hpp"

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

World world;

Map map{{
    .gen_interval = 1.0,
    .food_exists_gens = 10,
    .gen_food_count = 100, // 1000,
    .size = WORLD_SIZE,
    .min_food_weight = 1,
    .max_food_weight = 5,
    .food_color = {color::RED},
}};

Player player{canvas::SnakeObject::Config{
                  .obj = {.pos = {}, .color = {color::GREEN}},
                  .initial_length = 10,
                  .radius = 10,
              },
              Snake::Config{
                  .speed = 200.0,
                  .move_interval = 0.01,
              },
              map};

// std::vector<Bot> bots; // TODO

// this function is called to update game data,
// dt - time elapsed since the previous update (in seconds)
void act(float dt) {
  if (is_key_pressed(VK_ESCAPE)) {
    schedule_quit_game();
  }

  map.act(dt);

  player.act(dt);

  game_time += dt;
  world.prev_cursor = world.cursor;

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

  Veci map_offset = Veci(player.get_pos());

  player.draw(map_offset);
  map.draw(map_offset);
}

// free game data in this function
void finalize() {}
