#ifndef GRAPHICS_H
#define GRAPHICS_H

#include "globals.h"

void Text::draw() {
    dimensions = MeasureTextEx(*font, text.c_str(), size*((float)GetScreenHeight()/1080), spacing);

    Vector2 pos = {
            (screen_size.x * offsetPercent.x) - (0.5f * dimensions.x),
            (screen_size.y * offsetPercent.y) - (0.5f * dimensions.y)
    };
    DrawTextEx(*font, text.c_str(), pos, dimensions.y, spacing, color);
}

void MultilineText::draw() {
    for (int i = 0; i < lines.size(); i++) {
        Text(lines[i], color, size, {offsetPercent.x+dOffset.x*i, offsetPercent.y+dOffset.y*i}, spacing, font).draw();
    }
}

void Prompt::draw() {
    Vector2 size = {0,0};
    size.y = title.size +(contents.dOffset.y * screen_size.y * static_cast<float>(contents.lines.size()));
    for (auto &el : contents.lines) {
        if (MeasureTextEx(*contents.font, el.c_str(), contents.size, contents.spacing).x > size.x)
            size.x = MeasureTextEx(*contents.font, el.c_str(), contents.size, contents.spacing).x;
    }
    Vector2 sizePercent = {((screen_size.x - size.x) * 0.5f) / screen_size.x, ((screen_size.y - size.y) * 0.5f) / screen_size.y};
    title.reposition({0.5f, sizePercent.y});
    contents.reposition({0.5f, sizePercent.y + ((title.size + 30.0f) / screen_size.y)});
    OK.reposition({0.5f, ((size.y + screen_size.y) * 0.52f) / screen_size.y});

    DrawRectangle((screen_size.x - size.x) * 0.5f - 80.0f, (screen_size.y - size.y) * 0.5f - 80.0f, size.x + 160.0f, size.y + 160.0f, BLACK);
    DrawRectangleLinesEx({(screen_size.x - size.x) * 0.5f - 80.0f, (screen_size.y - size.y) * 0.5f - 80.0f, size.x + 160.0f, size.y + 160.0f}, 5.0f, WHITE);

    title.draw();
    contents.draw();
    OK.draw();
}

void derive_graphics_metrics_from_loaded_level() {
    Level* level = LevelManager::getInstance();

    screen_size.x  = static_cast<float>(GetScreenWidth());
    screen_size.y = static_cast<float>(GetScreenHeight());

    cell_size = std::min(
        screen_size.x / static_cast<float>(level->width()),
        screen_size.y / static_cast<float>(level->height())
    ) * CELL_SCALE;
    screen_scale = std::min(
        screen_size.x,
        screen_size.y
    ) / SCREEN_SCALE_DIVISOR;
    float level_width  = static_cast<float>(level->width()) * cell_size;
    float level_height = static_cast<float>(level->height())    * cell_size;
    shift_to_center.x = (screen_size.x - level_width) * 0.5f;
    shift_to_center.y = (screen_size.y - level_height) * 0.5f;
}

void draw_menu() {
    game_title.draw();
    game_subtitle.draw();
}

void draw_game_overlay() {
    Text score(
        std::to_string(player.get_coins()),
        YELLOW,
        40*screen_scale,
        {0.06f, 0.045f}
    );

    float coinSize = 60*screen_scale;
    draw_sprite(coin_sprite, {0, 0}, coinSize);
    score.draw();

    float heartSize = 60 * screen_scale;
    Vector2 heartsPosition = {(screen_size.x - heartSize*3) / 2, screen_size.y - heartSize};
    for (int i = 0; i < player.get_lives(); i++) {
        draw_image(heart_image, heartsPosition, heartSize);
        heartsPosition.x += heartSize;
    }
}

void LevelManager::draw() {
    Level* level = LevelManager::getInstance();

    for (size_t row = 0; row < level->rows; ++row) {
        for (size_t column = 0; column < level->columns; ++column) {

            Vector2 pos = {
                    shift_to_center.x + static_cast<float>(column) * cell_size,
                    shift_to_center.y + static_cast<float>(row) * cell_size
            };

            char cell = level->get_cell(row, column);
            switch(cell) {
                case Level::AIR:
                case Level::PLAYER:
                case Level::COIN:
                case Level::EXIT:
                case Level::SPIKE:
                    draw_image(air_image, pos, cell_size);
                    break;
                case Level::WALL:
                    draw_image(wall_image, pos, cell_size);
                    break;
            }

            switch (cell) {
                case Level::COIN:
                    draw_sprite(coin_sprite, pos, cell_size);
                    break;
                case Level::EXIT:
                    draw_image(exit_image, pos, cell_size);
                    break;
                case Level::SPIKE:
                    draw_image(spike_image, pos, cell_size);
                default:
                    break;
            }
        }
    }

    player.draw();
}

void Player::draw() {
    Vector2 position = {
            shift_to_center.x + pos.x * cell_size,
            shift_to_center.y + pos.y * cell_size
    };

    if (is_in_air) {
        draw_image((is_looking_forward ? player_jump_forward_image : player_jump_backwards_image), position, cell_size);
    }
    else if (is_moving) {
        draw_sprite((is_looking_forward ? player_walk_forward_sprite : player_walk_backwards_sprite), position, cell_size);
        is_moving = false;
    }
    else {
        draw_image((is_looking_forward ? player_stand_forward_image : player_stand_backwards_image), position, cell_size);
    }
}

void draw_pause_menu() {
    game_paused.draw();
}

void create_victory_menu_background() {
    for (auto &ball : victory_balls) {
        ball.x  = rand_up_to(screen_size.x);
        ball.y  = rand_up_to(screen_size.y);
        ball.dx = rand_from_to(-VICTORY_BALL_MAX_SPEED, VICTORY_BALL_MAX_SPEED);
        ball.dx *= screen_scale;
        if (abs(ball.dx) < 0E-1) ball.dx = 1.0f;
        ball.dy = rand_from_to(-VICTORY_BALL_MAX_SPEED, VICTORY_BALL_MAX_SPEED);
        ball.dy *= screen_scale;
        if (abs(ball.dy) < 0E-1) ball.dy = 1.0f;
        ball.radius = rand_from_to(VICTORY_BALL_MIN_RADIUS, VICTORY_BALL_MAX_RADIUS);
        ball.radius *= screen_scale;
    }

    /* Clear both the front buffer and the back buffer to avoid ghosting of the game graphics. */
    ClearBackground(BLACK);
    EndDrawing();
    BeginDrawing();
    ClearBackground(BLACK);
    EndDrawing();
    BeginDrawing();
}

void animate_victory_menu_background() {
    for (auto &ball : victory_balls) {
        ball.x += ball.dx;
        if (ball.x - ball.radius < 0 ||
            ball.x + ball.radius >= screen_size.x) {
            ball.dx = -ball.dx;
        }
        ball.y += ball.dy;
        if (ball.y - ball.radius < 0 ||
            ball.y + ball.radius >= screen_size.y) {
            ball.dy = -ball.dy;
        }
    }
}

void draw_victory_menu_background() {
    for (auto &ball : victory_balls) {
        DrawCircleV({ ball.x, ball.y }, ball.radius, VICTORY_BALL_COLOR);
    }
}

void draw_victory_menu() {
    DrawRectangle(
        0, 0,
        static_cast<int>(screen_size.x), static_cast<int>(screen_size.y),
        { 0, 0, 0, VICTORY_BALL_TRAIL_TRANSPARENCY }
    );

    animate_victory_menu_background();
    draw_victory_menu_background();

    victory_title.draw();
    victory_subtitle.draw();
}

#endif //GRAPHICS_H
