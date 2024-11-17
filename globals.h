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
        '#', '@', ' ', ' ', ' ', ' ', ' ', ' ', ' ', 'E', '#',
        '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#'
};

Level LEVEL_1 = {
        5, 11,
        LEVEL_1_DATA,
        10,
        0
};

char LEVEL_2_DATA[] = {
        '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#',
        '#', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', '#', '#', ' ', ' ', ' ', ' ', ' ', '#',
        '#', ' ', '*', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', '$', ' ', '#', '#', ' ', ' ', ' ', ' ', ' ', '#',
        '#', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', '#', '#', ' ', ' ', ' ', ' ', ' ', '#',
        '#', '#', '#', ' ', ' ', '#', ' ', ' ', ' ', '#', ' ', ' ', ' ', '#', '#', ' ', ' ', ' ', '#', ' ', '#',
        '#', ' ', ' ', ' ', ' ', '#', '^', '^', '^', '#', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', '#', ' ', '#',
        '#', ' ', ' ', ' ', ' ', '#', '#', '#', '#', '#', ' ', '<', ' ', ' ', ' ', '<', ' ', ' ', '#', ' ', '#',
        '#', ' ', ' ', ' ', ' ', '#', 'E', ' ', ' ', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', ' ', '#',
        '#', ' ', ' ', '#', '#', '#', '#', '#', ' ', '#', '$', '#', ' ', '#', ' ', ' ', ' ', ' ', ' ', ' ', '#',
        '#', ' ', ' ', ' ', ' ', '#', ' ', ' ', ' ', '#', ' ', ' ', ' ', '#', ' ', ' ', ' ', ' ', ' ', ' ', '#',
        '#', ' ', ' ', ' ', ' ', '#', ' ', '#', '#', '#', ' ', ' ', ' ', '#', ' ', '#', ' ', ' ', ' ', ' ', '#',
        '#', ' ', ' ', ' ', '@', '#', ' ', ' ', ' ', ' ', ' ', '#', ' ', ' ', ' ', '#', '^', '^', '#', '^', '#',
        '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#',
};

Level LEVEL_2 = {
        13, 21,
        LEVEL_2_DATA,
        20,
        1
};

char LEVEL_3_DATA[] = {
        '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#',
        '#', ' ', ' ', ' ', ' ', ' ', '#', ' ', ' ', ' ', ' ', ' ', ' ', ' ', '#', ' ', ' ', ' ', ' ', ' ', '#',
        '#', ' ', ' ', ' ', ' ', ' ', '#', ' ', ' ', ' ', '$', ' ', ' ', ' ', '#', ' ', ' ', ' ', ' ', ' ', '#',
        '#', ' ', '#', ' ', ' ', ' ', '#', ' ', ' ', ' ', '#', ' ', ' ', ' ', '#', ' ', ' ', ' ', '#', ' ', '#',
        '#', ' ', '#', ' ', ' ', ' ', '#', ' ', ' ', ' ', '#', ' ', ' ', ' ', '#', ' ', ' ', ' ', '#', ' ', '#',
        '#', ' ', '#', ' ', ' ', ' ', '#', ' ', '$', ' ', '#', ' ', ' ', ' ', '#', ' ', ' ', ' ', '#', ' ', '#',
        '#', ' ', '#', ' ', ' ', ' ', ' ', ' ', ' ', ' ', '#', ' ', ' ', ' ', ' ', ' ', ' ', ' ', '#', ' ', '#',
        '#', ' ', '#', ' ', ' ', ' ', ' ', ' ', ' ', ' ', '#', ' ', ' ', ' ', ' ', ' ', ' ', ' ', '#', ' ', '#',
        '#', ' ', '#', ' ', ' ', ' ', ' ', ' ', ' ', ' ', '#', ' ', ' ', ' ', '$', ' ', ' ', ' ', '#', ' ', '#',
        '#', ' ', '#', ' ', ' ', ' ', ' ', ' ', ' ', ' ', '#', ' ', ' ', ' ', ' ', ' ', ' ', ' ', '#', ' ', '#',
        '#', ' ', '#', ' ', ' ', ' ', ' ', ' ', ' ', ' ', '#', ' ', ' ', ' ', ' ', ' ', ' ', ' ', '#', ' ', '#',
        '#', '@', '#', '^', '^', '^', '^', '^', '^', '^', '#', '^', '^', '^', '^', '^', '^', '^', '#', 'E', '#',
        '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#',
};

Level LEVEL_3 = {
        13, 21,
        LEVEL_3_DATA,
        10
};

/* Player data */

Prompt *displayPrompt;

const float GRAVITY_FORCE = 0.01f;
const float JUMP_STRENGTH = 0.3f;
const float MOVEMENT_SPEED = 0.1f;

Player player;

/* Graphic Metrics */

const float CELL_SCALE = 0.8f; // An aesthetic parameter to add some negative space around level
const float SCREEN_SCALE_DIVISOR = 700.0f; // The divisor was found through experimentation
                                           // to scale things accordingly to look pleasant.

Vector2 screen_size;
float screen_scale; // Used to scale str/UI components size and displacements based on the screen_size size
float cell_size;
Vector2 shift_to_center;

/* Fonts */

Text death_title = {
    "You Died!",
    RED,
    100.0f,
    {0.50f, 0.50f},
};

Text death_subtitle = {
    "Press Enter to try again",
    WHITE,
    50.0f,
    {0.50f, 0.65f}
};

Text game_over_title = {
    "This is not how it ends.",
    RED,
    100.0f,
    {0.50f, 0.50f},
};

/* Images and Sprites */

Texture2D wall_image;
Texture2D air_image;
Texture2D exit_no_keys;
Texture2D exit_keys_closed;
Texture2D exit_keys_open;
Texture2D spike_image;

Texture2D heart_image;
Texture2D key_image;
Texture2D key_outline_image;
Texture2D ability_image;

Texture2D player_stand_forward_image;
Texture2D player_stand_backwards_image;
Texture2D player_jump_forward_image;
Texture2D player_jump_backwards_image;
Texture2D player_dead_image;

Texture2D intro1;
Texture2D intro2;
Texture2D intro3;
Texture2D intro4;
Texture2D ending1;
Texture2D ending2;
Texture2D ending3;

Slideshow intro(220);
Slideshow ending(220);

struct sprite {
    size_t frame_count    = 0;
    size_t frames_to_skip = 3;
    size_t frames_skipped = 0;
    size_t frame_index    = 0;
    bool loop = true;
    size_t prev_game_frame = 0;
    Texture2D *frames = nullptr;
};

sprite electro_sprite;
sprite coin_sprite;
sprite key_sprite;
sprite player_walk_forward_sprite;
sprite player_walk_backwards_sprite;

/* Sounds */

Sound coin_sound;
Sound exit_sound;
Sound scroll;
Sound forward;
Sound backout;

Music theme;
Music main_theme;
Music game;
Music idle;

/* Victory Menu Background */

/* Game States */

Menu main_menu({
        {"Play",         [] { game_state = GAME_STATE; SetExitKey(0); LevelManager::load();}},
        {"Options",         [] { game_state = OPTIONS_STATE;}},
        {"Exit",         [] { CloseWindow(); }}
}, [] {CloseWindow();}, WHITE, GRAY, 50.0f, {0.2f, 0.45f}, {0.0f, 0.075f});
Text main_menu_title("Quixote", GRAY, 80.0f, {0.2f, 0.2f}, 4.0f);
Text main_menu_byline("By @lunamaltseva", GRAY, 30.0f, {0.2f, 0.85f}, 2.0f);


extern OptionsMenu optionsMenu;
Text optionsMenuTitle("Settings", WHITE, 75.0f, {0.43f, 0.205f}, 4.0f);
OptionsMenu optionsMenu({
        {"Jump", []          {optionsMenu.getKey();}},
        {"Move Left", []        {optionsMenu.getKey();}},
        {"Move Right", []        {optionsMenu.getKey();}},
}, [] { game_state = MENU_STATE;}, WHITE, GRAY, 40.0f, {0.4f, 0.4f}, {0.0f, 0.05f});

MultilineText pauseMenuTitle("Bear It Out\neven to the\nEdge of Doom", {0.0f, 0.075f}, RED, 70.0f, {0.5f, 0.2f});
Menu pauseMenu({
                       {"Continue",  [] {game_state = GAME_STATE;}},
                       {"Restart",   [] {LevelManager::load(); game_state = GAME_STATE; player.kill();}},
                       {"Main menu", [] {game_state = MENU_STATE; LevelManager::reset();}}
               }, [] { game_state = GAME_STATE;}, WHITE, GRAY, 50.0f, {0.5f, 0.6f}, {0.0f, 0.075f});
/* Forward Declarations */

// GRAPHICS_H

void derive_graphics_metrics_from_loaded_level();
void draw_menu();
void draw_game_overlay();
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