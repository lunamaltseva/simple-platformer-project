#ifndef GLOBALS_H
#define GLOBALS_H

#include "raylib.h"
#include "lunalib.h"

#include <string>
#include <cstddef>
#include <cmath>

char LEVEL_1_DATA[] = {
        '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#',
        '#', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', '#',
        '#', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', '#',
        '#', ' ', ' ', ' ', ' ', '*', ' ', ' ', ' ', ' ', '#',
        '#', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', '#',
        '#', ' ', '@', ' ', ' ', ' ', ' ', ' ', 'E', ' ', '#',
        '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#'
};

Level LEVEL_1 = {
        7, 11,
        LEVEL_1_DATA
};

char LEVEL_2_DATA[] = {
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

Level LEVEL_2 = {
    11, 17,
    LEVEL_2_DATA
};

char LEVEL_3_DATA[] = {
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

Level LEVEL_3 = {
    13, 6,
    LEVEL_3_DATA
};

/* Player data */

const float GRAVITY_FORCE = 0.01f;
const float JUMP_STRENGTH = 0.3f;
const float MOVEMENT_SPEED = 0.1f;

Player player;

int player_score = 0;

/* Graphic Metrics */

const float CELL_SCALE = 0.8f; // An aesthetic parameter to add some negative space around level
const float SCREEN_SCALE_DIVISOR = 700.0f; // The divisor was found through experimentation
                                           // to scale things accordingly to look pleasant.

Vector2 screen_size;
float screen_scale; // Used to scale str/UI components size and displacements based on the screen_size size
float cell_size;
Vector2 shift_to_center;

/* Fonts */

Text game_title(
    "Platformer",
    RED,
    100.0f,
    {0.50f, 0.50f}
);

Text game_subtitle = {
    "Press Enter to Start",
    WHITE,
    50.0f,
    {0.50f, 0.65f}
};

Text game_paused = {
    "Press Escape to Resume"
};

Text victory_title = {
    "You Won!",
    RED,
    100.0f,
    {0.50f, 0.50f},
};

Text victory_subtitle = {
    "Press Enter to go back to menu",
    WHITE,
    50.0f,
    {0.50f, 0.65f}
};

/* Images and Sprites */

Texture2D wall_image;
Texture2D air_image;
Texture2D exit_image;

Texture2D heart_image;

Texture2D player_stand_forward_image;
Texture2D player_stand_backwards_image;
Texture2D player_jump_forward_image;
Texture2D player_jump_backwards_image;

struct sprite {
    size_t frame_count    = 0;
    size_t frames_to_skip = 3;
    size_t frames_skipped = 0;
    size_t frame_index    = 0;
    bool loop = true;
    size_t prev_game_frame = 0;
    Texture2D *frames = nullptr;
};

sprite coin_sprite;
sprite player_walk_forward_sprite;
sprite player_walk_backwards_sprite;

/* Sounds */

Sound coin_sound;
Sound exit_sound;

/* Victory Menu Background */

struct victory_ball {
    float x, y;
    float dx, dy;
    float radius;
};

const size_t VICTORY_BALL_COUNT     = 2000;
const float VICTORY_BALL_MAX_SPEED  = 2.0f;
const float VICTORY_BALL_MIN_RADIUS = 2.0f;
const float VICTORY_BALL_MAX_RADIUS = 3.0f;
const Color VICTORY_BALL_COLOR      = { 180, 180, 180, 255 };
const unsigned char VICTORY_BALL_TRAIL_TRANSPARENCY = 10;
victory_ball victory_balls[VICTORY_BALL_COUNT];

/* Game States */

enum game_state {
    MENU_STATE,
    GAME_STATE,
    PAUSED_STATE,
    VICTORY_STATE
};
game_state game_state = MENU_STATE;

/* Forward Declarations */

// GRAPHICS_H

void derive_graphics_metrics_from_loaded_level();
void draw_menu();
void draw_game_overlay();
void draw_pause_menu();
void create_victory_menu_background();
void animate_victory_menu_background();
void draw_victory_menu_background();
void draw_victory_menu();

// LEVEL_H

bool is_colliding(Vector2 pos, char look_for = '#');
char& get_collider(Vector2 pos, char look_for);

// ASSETS_H

void load_fonts();
void unload_fonts();

void load_images();
void unload_images();

void draw_image(Texture2D image, Vector2 pos, float width, float height);
void draw_image(Texture2D image, Vector2 pos, float size);

sprite load_sprite(
        const std::string &file_name_prefix,
        const std::string &file_name_suffix,
        size_t frame_count = 1,
        bool loop = true,
        size_t frames_to_skip = 3
);
void unload_sprite(sprite &sprite);
void draw_sprite(sprite &sprite, Vector2 pos, float width, float height);
void draw_sprite(sprite &sprite, Vector2 pos, float size);

void load_sounds();
void unload_sounds();

// UTILITIES_H

float rand_from_to(float from, float to);
float rand_up_to(float to);

#endif // GLOBALS_H