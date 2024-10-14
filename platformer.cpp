#include "raylib.h"
#include <iostream>

#include "globals.h"
#include "images.h"
#include "graphics.h"
#include "level.h"
#include "player.h"
#include "utilities.h"

void update_game() {
    game_frame++;

    if (IsKeyDown(KEY_RIGHT) || IsKeyDown(KEY_D)) {
        move_player_horizontally(movement_speed);
    }

    if (IsKeyDown(KEY_LEFT) || IsKeyDown(KEY_A)) {
        move_player_horizontally(-movement_speed);
    }

    bool is_player_on_ground = is_colliding({player_pos.x, player_pos.y + 0.1f}, WALL);
    if ((IsKeyDown(KEY_UP) || IsKeyDown(KEY_W) || IsKeyDown(KEY_SPACE)) && is_player_on_ground) {
        player_y_velocity = -jump_strength;
    }

    update_player();
}

void draw_game() {
    draw_level();
}

int main() {
    SetConfigFlags(FLAG_VSYNC_HINT);
    InitWindow(GetScreenWidth(), GetScreenHeight(), "Platformer");
    SetTargetFPS(60);
    ToggleFullscreen();
    HideCursor();

    load_images();
    load_level();

    while (!WindowShouldClose()) {
        BeginDrawing();
        ClearBackground(BLACK);

        update_game();
        draw_game();

        EndDrawing();
    }
    CloseWindow();

    return 0;
}
