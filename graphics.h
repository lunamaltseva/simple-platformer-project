#ifndef GRAPHICS_H
#define GRAPHICS_H

#include "globals.h"
#include <iomanip>

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
    int minimum = std::min(screen_size.x, screen_size.y);
    float scale = minimum*0.25f;
    draw_image(exit_no_keys, {screen_size.x - (scale * 1.75f), screen_size.y - (scale * 1.5f)}, scale);
    draw_sprite(player_walk_forward_sprite, {screen_size.x - (scale * 3.0f), screen_size.y - (scale * 1.5f)}, scale);
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

    float heart_size = 60 * screen_scale;
    Vector2 hearts_position{(screen_size.x - heart_size * (float) player.get_lives()) / 2, screen_size.y - heart_size};
    for (int i = 0; i < player.get_lives(); i++) {
        draw_image(heart_image, hearts_position, heart_size);
        hearts_position.x += heart_size;
    }

    float key_size = 60 * screen_scale;
    Vector2 key_position{screen_size.x - key_size, screen_size.y - key_size};
    for (int i = 0; i < LevelManager::getInstance()->keys_total(); i++) {
        draw_image((player.get_keys() > i ? key_image : key_outline_image), key_position, key_size);
        key_position.y -= key_size;
    }

    unsigned char colorDelta = abs(sin((game_frame/120.f) * 3.14159265358979323846))*250;
    Color color({255, colorDelta, colorDelta, 255});
    Text time (
            std::to_string(LevelManager::getInstance()->time()/60) + "s",
            (LevelManager::getInstance()->time() < 600 ? color : WHITE),
            40*screen_scale,
            {0.94f, 0.045f}
    );
    time.draw();

    if (player.get_coins() > 0) {
        float ability_icon_size = 60 * screen_scale;
        Vector2 ability_icon_position{0, screen_size.y - key_size};
        draw_image(ability_image, ability_icon_position, ability_icon_size);
        ability_icon_position.y -= ability_icon_size;
        draw_sprite(coin_sprite, ability_icon_position, ability_icon_size);

        Text double_jump(
                "Double Jump",
                WHITE,
                20*screen_scale,
                {0.15f, 0.953f}
        );
        double_jump.draw();
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
                case Level::KEY:
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
                    draw_image((level->keys == 0 ? exit_no_keys : (LevelManager::getInstance()->keys_total() <= player.get_keys() ? exit_keys_open : exit_keys_closed)), pos, cell_size);
                    break;
                case Level::SPIKE:
                    draw_image(spike_image, pos, cell_size);
                    break;
                case Level::KEY:
                    draw_sprite(key_sprite, pos, cell_size);
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

    if (game_state != YOU_DIED_STATE) {
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
    else draw_image(player_dead_image, position, cell_size);
}

void ElectroManager::draw() {
    for (auto &electro : arr) {
        Vector2 position = {
                shift_to_center.x + electro.x * cell_size,
                shift_to_center.y + electro.y * cell_size
        };
        draw_sprite(electro_sprite, position, cell_size);
    }
}

#endif //GRAPHICS_H
