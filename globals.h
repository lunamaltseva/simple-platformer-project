#ifndef GLOBALS_H
#define GLOBALS_H

#include "raylib.h"

#include <string>
#include <cstddef>

/* Game Elements */

const char WALL           = '#';
const char PLAYER         = '@';
const char FLOOR          = ' ';

/* Levels */

struct level {
    size_t rows = 0, columns = 0;
    char *data = nullptr;
};

char LEVEL_1_DATA[] = {
    '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#',  '#',
    '#', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ',  '#',
    '#', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ',  '#',
    '#', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ',  '#',
    '#', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ',  '#',
    '#', '#', '#', '#', '#', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ',  '#',
    '#', '#', '#', '#', '#', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ',  '#',
    '#', '#', '#', '#', '#', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ',  '#',
    '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#',  '#',
};

level LEVEL_1 = {
    9, 16,
    LEVEL_1_DATA
};

/* Images and Sprites */

Texture2D wall_image;
Texture2D floor_image;

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

#endif // GLOBALS_H
