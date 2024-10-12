#ifndef LEVEL_H
#define LEVEL_H

#include "globals.h"

void load_level(int offset) {
    level_index += offset;
    current_level.columns = LEVELS[level_index].columns;
    current_level.rows = LEVELS[level_index].rows;
    current_level.data = LEVELS[level_index].data;

    for (size_t row = 0; row < current_level.rows; ++row) {
        for (size_t column = 0; column < current_level.columns; ++column) {
            char cell = current_level.data[row * LEVEL_1.columns + column];

            if (cell == PLAYER) {
                player_hitbox_offset.x = column;
                player_hitbox_offset.y = row;
                return;
            }
        }
    }
}

#endif //LEVEL_H
