#ifndef LEVEL_H
#define LEVEL_H

#include "globals.h"

char& Level::get_cell(size_t row, size_t column) {
    return data[row * columns + column];
}

void Level::set_cell(size_t row, size_t column, char cell) {
    data[row * columns + column] = cell;
}

bool is_colliding(Vector2 pos, char look_for) {
    Level* level = LevelManager::getInstance();
    Rectangle player_hitbox = {pos.x, pos.y, 1.0f, 1.0f};

    for (size_t row = 0; row < level->height(); ++row) {
        for (size_t column = 0; column < level->width(); ++column) {
            if (level->get_cell(row, column) == look_for) {
                Rectangle block_hitbox = {(float) column, (float) row, 1.0f, 1.0f};
                if (CheckCollisionRecs(player_hitbox, block_hitbox)) {
                    return true;
                }
            }
        }
    }
    return false;
}

char& get_collider(Vector2 pos, char look_for) {
    Level* level = LevelManager::getInstance();
    Rectangle player_hitbox = {pos.x, pos.y, 1.0f, 1.0f};

    for (size_t row = 0; row < level->height(); ++row) {
        for (size_t column = 0; column < level->width(); ++column) {
            if (level->get_cell(row, column) == look_for) {
                Rectangle block_hitbox = {(float) column, (float) row, 1.0f, 1.0f};
                if (CheckCollisionRecs(player_hitbox, block_hitbox)) {
                    return level->get_cell(row, column);
                }
            }
        }
    }

    return level->get_cell(roundf(pos.y), roundf(pos.x));
}

void LevelManager::load(size_t offset) {
    index += offset;

    if (index >= get_size()) {
        game_state = VICTORY_STATE;
        create_victory_menu_background();
        index = 0;
        return;
    }

    Level* level = LevelManager::getInstance();

    level->rows    = levels[index].rows;
    level->columns = levels[index].columns;
    level->data = new char[level->rows * level->columns];

    for (size_t row = 0; row < level->rows; ++row) {
        for (size_t column = 0; column < level->columns; ++column) {
            char cell = levels[index].data[row * level->columns + column];
            if (cell == Level::PLAYER) {
                level->set_cell(row, column, Level::AIR);
                player.spawn(row, column);
            }
            else
                level->set_cell(row, column, cell);
        }
    }

    derive_graphics_metrics_from_loaded_level();
}

void LevelManager::unload() {
    delete LevelManager::getInstance();
}

#endif //LEVEL_H
