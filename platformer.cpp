#include "raylib.h"

#include "globals.h"
#include "images.h"
#include "graphics.h"
#include "level.h"
#include "utilities.h"

void update_game() {
    if (IsKeyDown(KEY_SPACE) && get_colliding_object(player_hitbox_offset.x, player_hitbox_offset.y + 0.1f, current_level) == '#') {
        player_gravity_velocity = -0.3f;
    }

    if (IsKeyDown(KEY_D) && get_colliding_object(player_hitbox_offset.x + 0.05f, player_hitbox_offset.y, current_level) != '#') {
        player_hitbox_offset.x+=0.1f;
    }
    if (IsKeyDown(KEY_A) && get_colliding_object(player_hitbox_offset.x - 0.05f, player_hitbox_offset.y, current_level) != '#') {
        player_hitbox_offset.x-=0.1f;
    }

    player_hitbox_offset.y += player_gravity_velocity;
    player_gravity_velocity += playerGravity;

    if (get_colliding_object(player_hitbox_offset.x, player_hitbox_offset.y + 0.1f, current_level) == '#') {
        player_gravity_velocity = 0;
        player_hitbox_offset.y = roundf(player_hitbox_offset.y);
    }

    if (get_colliding_object(player_hitbox_offset.x, player_hitbox_offset.y, current_level) == '#') {
        player_hitbox_offset.x = roundf(player_hitbox_offset.x);
    }
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
    load_level(0);

    while (!WindowShouldClose()) {
        game_frame++;

        BeginDrawing();
        ClearBackground(BLACK);

        update_game();
        draw_game();

        EndDrawing();
    }
    CloseWindow();

    return 0;
}
