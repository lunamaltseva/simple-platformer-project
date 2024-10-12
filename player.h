#ifndef PLAYER_H
#define PLAYER_H

#include "globals.h"

void spawn_player() {
    for (size_t row = 0; row < current_level.rows; ++row) {
        for (size_t column = 0; column < current_level.columns; ++column) {
            char cell = current_level.data[row * current_level.columns + column];

            if (cell == PLAYER) {
                player_hitbox_offset.x = column;
                player_hitbox_offset.y = row;
                return;
            }
        }
    }
}

#endif //PLAYER_H
