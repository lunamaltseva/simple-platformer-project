#include "raylib.h"

#include "globals.h"
#include "images.h"
#include <iostream>

void update_game() {

}

void draw_game() {

}

float tileSize = 1920./16;
float virtualSpaceResolution = 16;
const float player_move_speed = 1.3f;

char get_colliding_object(float x, float y, float size, level &level) {
    Rectangle a({x, y, size, size});

    for (size_t row = 0; row < level.rows; ++row) {
        for (size_t column = 0; column < level.columns; ++column) {
            Rectangle b({
            static_cast<float>(column) * virtualSpaceResolution,
            static_cast<float>(row) * virtualSpaceResolution,
            virtualSpaceResolution,
            virtualSpaceResolution});

            if (CheckCollisionRecs(a, b))
                return level.data[row * level.columns + column];
        }
    }
    return '\0';
}

int main() {
    SetConfigFlags(FLAG_VSYNC_HINT);
    InitWindow(GetScreenWidth(), GetScreenHeight(), "Platformer");
    SetTargetFPS(60);
    ToggleFullscreen();
    HideCursor();

    Texture2D wall_image = LoadTexture("data/images/wall.png");
    Texture2D floor_image = LoadTexture("data/images/floor.png");
    sprite player_sprite = load_sprite("data/images/player/player", ".png", 11);

    struct Player {
        Vector2 pos;
        Vector2 velocity;
    };

    Player player({2*32, 2*32});

    while (!WindowShouldClose()) {
        game_frame++;
        player.velocity.y += 0.1f;
        player.pos.y += player.velocity.y;

        if (player.velocity.y > 0 && get_colliding_object(player.pos.x, player.pos.y + virtualSpaceResolution, tileSize, LEVEL_1) == WALL) {
            player.velocity.y = 0;
            player.pos.y = virtualSpaceResolution * round(player.pos.y/virtualSpaceResolution);
        }

        else if (get_colliding_object(player.pos.x, player.pos.y, tileSize, LEVEL_1) == WALL)
                player.velocity.y = 0.5f;


        if (IsKeyDown(KEY_A)) {
            if (get_colliding_object(player.pos.x - player_move_speed, player.pos.y, tileSize, LEVEL_1) != WALL)
                player.pos.x -= player_move_speed;
            else
                player.pos.x = virtualSpaceResolution * round(player.pos.x / virtualSpaceResolution);
        }
        if (IsKeyDown(KEY_D)) {
            if (get_colliding_object(player.pos.x + player_move_speed + virtualSpaceResolution, player.pos.y, tileSize, LEVEL_1) != WALL)
                player.pos.x += player_move_speed;
            else
                player.pos.x = virtualSpaceResolution * round(player.pos.x / virtualSpaceResolution);
        }
        if (IsKeyDown(KEY_SPACE)) {
            if (get_colliding_object(player.pos.x, player.pos.y + virtualSpaceResolution, tileSize, LEVEL_1) == WALL)
            player.velocity.y = -3.1f;
        }

        BeginDrawing();
        ClearBackground(BLACK);

        for (size_t row = 0; row < LEVEL_1.rows; ++row) {
            for (size_t column = 0; column < LEVEL_1.columns; ++column) {
                float x = static_cast<float>(column) * tileSize;
                float y = static_cast<float>(row) * tileSize;

                char cell = LEVEL_1.data[row * LEVEL_1.columns + column];
                switch (cell) {
                    case WALL:
                        draw_image(wall_image, x, y, tileSize);
                        break;
                    default:
                        break;
                }
            }
        }

        draw_sprite(player_sprite, player.pos.x / virtualSpaceResolution * tileSize, player.pos.y / virtualSpaceResolution * tileSize, tileSize);

        EndDrawing();
    }
    CloseWindow();

    return 0;
}
