#include "raylib.h"

#include "globals.h"
#include "level.h"
#include "player.h"
#include "graphics.h"
#include "assets.h"
#include "lunalib_func.h"
#include "enemy.h"

class Game {
public:
    Game();
    ~Game();

    void update();
    void draw();
};

int main() {
    SetConfigFlags(FLAG_VSYNC_HINT);
    InitWindow(GetScreenWidth(), GetScreenHeight(), "Platformer");
    SetTargetFPS(60);
    ToggleFullscreen();
    HideCursor();
    InitAudioDevice();

    Game Quixote;

    while (!WindowShouldClose()) {
        ClearBackground(BLACK);
        BeginDrawing();

        Quixote.update();
        Quixote.draw();

        EndDrawing();
    }

    return 0;
}

Game::Game() {
    InitAudioDevice();

    LevelManager::add(LEVEL_1);
    LevelManager::add(LEVEL_2);
    LevelManager::add(LEVEL_3);

    load_fonts();
    load_images();
    load_sounds();

    LevelManager::load();
    SetExitKey(0);
}

void Game::update() {
    game_frame++;

    switch (game_state) {
        case INTRO_STATE:
            if (!intro.draw() || IsKeyPressed(KEY_ENTER)) {
                game_state = MENU_STATE;
                game_frame = 0;
            }
            play(theme);
            break;

        case GAME_STATE:
            play(game);
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
                PlaySound(air_jump_sound);
            }

            player.update();

            if (IsKeyPressed(KEY_ESCAPE)) {
                game_state = PAUSED_STATE;
                game_frame = 0;
                PlaySound(backout);
            }
            break;

        case PAUSED_STATE:
            play(game);
            if (IsKeyPressed(KEY_ESCAPE)) {
                game_state = GAME_STATE;
                PlaySound(forward);
            }
            break;

        case YOU_DIED_STATE:
            play(idle);
            if (IsKeyPressed(KEY_ENTER)) {
                game_state = (player.get_lives() <= 0 ? GAME_OVER_STATE : GAME_STATE);
                LevelManager::load();
            }
            break;

        case GAME_OVER_STATE:
            play(idle);
            if (IsKeyPressed(KEY_ENTER)) {
                player.reset();
                LevelManager::reset();
                game_state = GAME_STATE;
                LevelManager::load();
            }
            break;

        case ENDING_STATE:
            play(idle);
            if (!ending.draw()) {
                game_state = MENU_STATE;
                game_frame = 0;
            }
            break;
    }
}

void Game::draw() {
    switch(game_state) {
        case MENU_STATE:
            play(main_theme);
            if (game_frame != 0) main_menu.run();
            main_menu_byline.draw();
            main_menu_title.draw();
            draw_menu();
            break;

        case GAME_STATE:
            LevelManager::draw();
            ElectroManager::draw();
            draw_game_overlay();
            break;

        case OPTIONS_STATE:
            play(main_theme);
            main_menu.draw();
            main_menu_byline.draw();
            main_menu_title.draw();
            draw_menu();
            optionsMenu.run();
            optionsMenuTitle.draw();
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
            DrawRectangle(0, 0, screen_size.x, screen_size.y, {0, 0, 0, 210});
            if (game_frame != 0) pauseMenu.run();
            pauseMenuTitle.draw();
            break;

        case GAME_OVER_STATE:
            game_over_title.draw();
            game_over_subtitle.draw();
            game_frame = 0;
            break;
    }
}

Game::~Game() {
    LevelManager::unload();
    unload_sounds();
    unload_images();
    unload_fonts();

    CloseAudioDevice();
    CloseWindow();
}