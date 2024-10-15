#ifndef GLOBALS_H
#define GLOBALS_H

#include "raylib.h"
#include <string>
#include <cstddef>

/* Game Elements */

const char WALL   = '#';
const char AIR    = ' ';
const char PLAYER = '@';
const char COIN   = '*';
const char EXIT   = 'E';

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

level LEVEL_2 = {
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

level LEVEL_3 = {
    13, 6,
    LEVEL_3_DATA
};

level current_level;
int level_index = 0;
char *current_level_data;
const int LEVEL_COUNT = 3;

level LEVELS[LEVEL_COUNT] = {
        LEVEL_1, LEVEL_2, LEVEL_3
};

/* Player data */

Vector2 player_pos;
int player_score = 0;
float player_y_velocity = 0;
bool is_player_on_ground;
const float gravity = 0.01f;
const float jump_strength = 0.3f;
const float movement_speed = 0.1f;

/* Drawing accessories */

const float CELL_SCALE = 0.8f; // An aesthetic parameter to add some negative space around level
const float SCREEN_SCALE_DIVISOR = 700.0f; // The divisor was found through experimentation
// to scale things accordingly to look pleasant.

float screen_width;
float screen_height;
float screen_scale; // Used to scale str/UI components size and displacements based on the screen size
float cell_size;
float shift_to_center_cell_by_x;
float shift_to_center_cell_by_y;

/* Game States */

enum game_state {
    MENU_STATE,
    GAME_STATE,
    PAUSED_STATE,
    VICTORY_STATE
};
game_state game_state = MENU_STATE;

/* Images and Sprites */

Texture2D wall_image;
Texture2D exit_image;

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
sprite player_sprite;

/* Text */

Font menu_font;

struct Text {
    std::string str;
    Vector2 position = {0.50f, 0.50f};
    float size = 32.0f;
    Color color = WHITE;
    float spacing = 4.0f;
    Font* font = &menu_font;
};

Text game_title = {
        "Platformer",
        {0.50f, 0.50f},
        120.0f,
        RED
};

Text game_subtitle = {
        "Press Enter to Start",
        {0.50f, 0.65f}
};

Text game_paused = {
        "Press Escape to Resume"
};

Text victory_title = {
        "You Won!",
        {0.50f, 0.50f},
        120.0f,
        RED
};

Text victory_subtitle = {
        "Press Enter to go back to menu",
        {0.50f, 0.65f}
};

/* Frame Counter */

size_t game_frame = 0;

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

/* Forward Declarations */

// GRAPHICS_H

void derive_graphics_metrics_from_loaded_level();
void create_victory_menu_background();
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

float rand_from_to(float from, float to);
float rand_up_to(float to);
bool is_colliding(Vector2 pos, char look_for = '#', level &level = current_level);
char& get_collider(Vector2 pos, char look_for, level &level = current_level);

#endif // GLOBALS_H