#ifndef GLOBALS_H
#define GLOBALS_H

#include "raylib.h"
#include <string>
#include <cstddef>

/* Game Elements */

const char WALL           = '#';
const char AIR            = ' ';
const char PLAYER         = '@';
const char COIN           = '*';
const char EXIT           = 'E';

/* Levels */

struct level {
    size_t rows = 0, columns = 0;
    char *data = nullptr;
};

char LEVEL_1_DATA[] = {
        '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#',
        '#', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', '#',
        '#', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', '#',
        '#', ' ', ' ', ' ', ' ', '*', ' ', ' ', ' ', ' ', '#',
        '#', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', '#',
        '#', ' ', '@', ' ', ' ', ' ', ' ', ' ', 'E', ' ', '#',
        '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#'
};

level LEVEL_1 = {
        7, 11,
        LEVEL_1_DATA
};

char LEVEL_2_DATA[] = {
        '#', '#', '#', '#', '#', '#',
        '#', ' ', ' ', ' ', '*', '#',
        '#', ' ', ' ', ' ', ' ', '#',
        '#', '@', ' ', ' ', ' ', '#',
        '#', '#', '#', ' ', ' ', '#',
        '#', '*', ' ', ' ', ' ', '#',
        '#', ' ', ' ', ' ', ' ', '#',
        '#', ' ', ' ', ' ', ' ', '#',
        '#', ' ', ' ', '#', '#', '#',
        '#', ' ', ' ', ' ', ' ', '#',
        '#', ' ', ' ', ' ', ' ', '#',
        '#', ' ', ' ', ' ', 'E', '#',
        '#', '#', '#', '#', '#', '#'
};

level LEVEL_2 = {
        13, 6,
        LEVEL_2_DATA
};

char LEVEL_3_DATA[] = {
    '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#',
    '#', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', '#',
    '#', ' ', ' ', ' ', ' ', ' ', ' ', ' ', '*', ' ', ' ', ' ', ' ', ' ', ' ', ' ', '#',
    '#', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', '#',
    '#', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', '#',
    '#', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', '#',
    '#', ' ', ' ', ' ', '#', '#', ' ', ' ', ' ', ' ', ' ', '#', '#', ' ', ' ', ' ', '#',
    '#', ' ', ' ', ' ', '#', '#', ' ', ' ', ' ', ' ', ' ', '#', '#', ' ', ' ', ' ', '#',
    '#', ' ', ' ', ' ', '#', '#', ' ', ' ', ' ', ' ', ' ', '#', '#', ' ', ' ', ' ', '#',
    '#', ' ', '@', ' ', '#', '#', ' ', ' ', ' ', ' ', ' ', '#', '#', ' ', 'E', ' ', '#',
    '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#'
};

level LEVEL_3 = {
    11, 17,
    LEVEL_3_DATA
};

level current_level;
int level_index = 0;
const int LEVEL_COUNT = 3;

level LEVELS[LEVEL_COUNT] = {
        LEVEL_1, LEVEL_2, LEVEL_3
};

/* Player data */

Vector2 player_pos;
float player_y_velocity = 0;
const float gravity = 0.01f;
const float jump_strength = 0.3f;
const float movement_speed = 0.1f;

/* Drawing accessories */

const float CELL_SCALE = 0.8f; // An aesthetic parameter to add some negative space around level
const float SCREEN_SCALE_DIVISOR = 700.0f; // The divisor was found through experimentation
// to scale things accordingly to look pleasant.

float screen_width;
float screen_height;
float screen_scale; // Used to scale text/UI components size and displacements based on the screen size
float cell_size;
float shift_to_center_cell_by_x;
float shift_to_center_cell_by_y;

/* Images and Sprites */

Texture2D wall_image;
Texture2D exit_image;
Texture2D coin_image;

struct sprite {
    size_t frame_count    = 0;
    size_t frames_to_skip = 3;
    size_t frames_skipped = 0;
    size_t frame_index    = 0;
    bool loop = true;
    size_t prev_game_frame = 0;
    Texture2D *frames = nullptr;
};

sprite player_sprite;

/* Frame Counter */

size_t game_frame = 0;

/* Game State */

/* Forward Declarations */

// GRAPHICS_H

void draw_image(Texture2D image, float x, float y, float width, float height);
void draw_image(Texture2D image, float x, float y, float size);

sprite load_sprite(
    const std::string &file_name_prefix,
    const std::string &file_name_suffix,
    size_t frame_count = 1,
    bool loop = true,
    size_t frames_to_skip = 3
);
void unload_sprite(sprite &sprite);
void draw_sprite(sprite &sprite, float x, float y, float width, float height);
void draw_sprite(sprite &sprite, float x, float y, float size);
void draw_player();

// PLAYER_H

void spawn_player();

// UTILITIES_H

bool is_colliding(Vector2 pos, char look_for = '#', level &level = current_level);
char& get_collider(Vector2 pos, char look_for, level &level = current_level);

#endif // GLOBALS_H