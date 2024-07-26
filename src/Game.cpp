#include <cstdlib>
#include <cstring>
#include <ctime>
#include <iostream>
#include <vector>

// #include <stdio.h>

#include "Bot.hpp"
#include "Engine.h"
#include "Map.hpp"
#include "Params.hpp"
#include "Player.hpp"
#include "Snake.hpp"
#include "Text.hpp"
#include "Utils.hpp"

namespace world {
Map map{{
    .gen_interval = 1.0,
    .food_exists_gens = 10,
    .gen_food_count = 100, // 1000,
    .size = WORLD_SIZE,
    .min_food_weight = 1,
    .max_food_weight = 5,
    .food_color = {color::RED},
}};

Player player{default_snake_object_config<{color::GREEN}>,
              {
                  .speed = 200.0,
                  .move_interval = 0.01,
              },
              map};

std::vector<Bot> bots;
} // namespace world

std::vector<Bot> gen_bots(Veci player_pos, Map &map) {
  std::vector<Bot> bots;

  bots.reserve(WORLD_SIZE.x * WORLD_SIZE.y /
               (BOT_GEN_INTERVAL * BOT_GEN_INTERVAL));
  for (int x = 0; x < WORLD_SIZE.x; x += BOT_GEN_INTERVAL) {
    for (int y = 0; y < WORLD_SIZE.y; y += BOT_GEN_INTERVAL) {
      Veci pos{
          .x = x +
               utils::rand_in_range(-BOT_GEN_RAND_OFFSET, BOT_GEN_RAND_OFFSET),
          .y = y -
               utils::rand_in_range(-BOT_GEN_RAND_OFFSET, BOT_GEN_RAND_OFFSET),
      };
      if ((player_pos - pos).len_sq() >=
          MIN_BOT_GEN_DISTANCE * MIN_BOT_GEN_DISTANCE) {
        bots.push_back(default_bot(pos, map));
      }
    }
  }

  return bots;
}

// initialize game data in this function
void initialize() {
  std::srand(std::time(0));

  world::bots = gen_bots(world::player.get_pos() + utils::get_screen_center(),
                         world::map);
}

// this function is called to update game data,
// dt - time elapsed since the previous update (in seconds)
void act(float dt) {
  if (is_key_pressed(VK_ESCAPE)) {
    schedule_quit_game();
  }

  world::player.act(dt);

  for (auto it = world::bots.begin(); it != world::bots.end();) {
    it->act(dt);

    if (world::player.touches(*it)) { // GAME OVER
      std::cout << "game over :(\nfinal score is " << world::player.get_score()
                << std::endl;
      schedule_quit_game();
    }
    ++it;
  }

  world::map.act(dt);
}

void draw_score() {
  paint::text({
      {
          .pos = {.x = 10, .y = 10},
          .color = {color::BLUE},
      },
      5,
      world::player.get_score(),
  });
}

// fill buffer in this function
// uint32_t buffer[SCREEN_HEIGHT][SCREEN_WIDTH] - is an array of 32-bit colors
// (8 bits per R, G, B)
void draw() {
  // clear backbuffer
  std::memset(buffer, 0, SCREEN_HEIGHT * SCREEN_WIDTH * sizeof(uint32_t));

  Veci map_offset = Veci(world::player.get_pos());

  world::player.draw(map_offset);

  for (const auto &bot : world::bots) {
    bot.draw(map_offset);
  }

  world::map.draw(map_offset);

  draw_score();
}

// free game data in this function
void finalize() {}
