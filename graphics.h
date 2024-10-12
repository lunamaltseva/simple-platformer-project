#ifndef GRAPHICS_H
#define GRAPHICS_H

#include "globals.h"

void draw_level() {
    for (size_t row = 0; row < current_level.rows; ++row) {
        for (size_t column = 0; column < current_level.columns; ++column) {
            float x = static_cast<float>(column) * tileSize;
            float y = static_cast<float>(row) * tileSize;

            char cell = current_level.data[row * current_level.columns + column];
            switch (cell) {
                case WALL:
                    draw_image(wall_image, x, y, tileSize);
                    break;
                case COIN:

                    break;
                default:
                    break;
            }
        }
    }

    draw_sprite(player_sprite, player_hitbox_offset.x * tileSize, player_hitbox_offset.y * tileSize, tileSize);
}

#endif //GRAPHICS_H
