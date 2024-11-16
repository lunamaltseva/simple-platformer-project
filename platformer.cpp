#include "raylib.h"

#include "globals.h"
#include "level.h"
#include "player.h"
#include "graphics.h"
#include "assets.h"
#include "utilities.h"

void update_game() {
    game_frame++;

    switch (game_state) {
        case MENU_STATE:
            if (IsKeyPressed(KEY_ENTER)) {
                SetExitKey(0);
                game_state = GAME_STATE;
                LevelManager::load();
            }
            break;

        case GAME_STATE:
            ElectroManager::update();

            if (LevelManager::getInstance()->countdown() < 60) {
                player.kill();
            }

            if (IsKeyDown(KEY_RIGHT) || IsKeyDown(KEY_D)) {
                player.move_horizontally(MOVEMENT_SPEED);
            }

            if (IsKeyDown(KEY_LEFT) || IsKeyDown(KEY_A)) {
                player.move_horizontally(-MOVEMENT_SPEED);
            }

            // Calculating collisions to decide whether the player is allowed to jump: don't want them to suction cup to the ceiling or jump midair
            if ((IsKeyDown(KEY_UP) || IsKeyDown(KEY_W) || IsKeyDown(KEY_SPACE)) && player.is_player_on_ground()) {
                player.set_y_velocity(-JUMP_STRENGTH);
            }

            else if ((IsKeyPressed(KEY_UP) || IsKeyPressed(KEY_W) || IsKeyPressed(KEY_SPACE)) && player.get_coins() > 0) {
                player.set_y_velocity(-JUMP_STRENGTH);
                player.lose_coins(1);
            }

            player.update();

            if (IsKeyPressed(KEY_ESCAPE)) {
                game_state = PAUSED_STATE;
            }
            break;

        case PAUSED_STATE:
            if (IsKeyPressed(KEY_ESCAPE)) {
                game_state = GAME_STATE;
            }
            break;

        case YOU_DIED_STATE:
            if (IsKeyPressed(KEY_ENTER)) {
                LevelManager::load();
                game_state = GAME_STATE;
            }
            break;

        case GAME_OVER_STATE:
            if (IsKeyPressed(KEY_ENTER)) {
                player.reset();
                LevelManager::reset();
                LevelManager::load();
                game_state = GAME_STATE;
            }
            break;

        case VICTORY_STATE:
            if (IsKeyPressed(KEY_ENTER) || IsKeyPressed(KEY_ESCAPE)) {
                SetExitKey(KEY_ESCAPE);
                game_state = MENU_STATE;
            }
            break;
    }
}

void draw_game() {
    switch(game_state) {
        case MENU_STATE:
            draw_menu();
            break;

        case GAME_STATE:
            LevelManager::draw();
            ElectroManager::draw();
            draw_game_overlay();
            break;

        case YOU_DIED_STATE:
            LevelManager::draw();
            ElectroManager::draw();
            draw_game_overlay();
            DrawRectangle(0, 0, screen_size.x, screen_size.y, {0, 0, 0, 150});
            death_title.draw();
            death_subtitle.draw();
            break;

        case PAUSED_STATE:
            LevelManager::draw();
            ElectroManager::draw();
            draw_game_overlay();
            DrawRectangle(0, 0, screen_size.x, screen_size.y, {0, 0, 0, 150});
            draw_pause_menu();
            break;

        case GAME_OVER_STATE:
            game_over_title.draw();
            death_subtitle.draw();
            break;

        case VICTORY_STATE:
            draw_victory_menu();
            break;
    }
}

int main() {
    SetConfigFlags(FLAG_VSYNC_HINT);
    InitWindow(GetScreenWidth(), GetScreenHeight(), "Platformer");
    SetTargetFPS(60);
    ToggleFullscreen();
    HideCursor();
    InitAudioDevice();

    LevelManager::add(LEVEL_1);
    LevelManager::add(LEVEL_2);
    LevelManager::add(LEVEL_3);

    load_fonts();
    load_images();
    load_sounds();
    LevelManager::load();

    while (!WindowShouldClose()) {
        ClearBackground(BLACK);
        BeginDrawing();

        update_game();
        draw_game();

        EndDrawing();
    }

    LevelManager::unload();
    unload_sounds();
    unload_images();
    unload_fonts();

    CloseAudioDevice();
    CloseWindow();

    return 0;
}
