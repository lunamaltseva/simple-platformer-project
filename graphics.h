#ifndef GRAPHICS_H
#define GRAPHICS_H

#include "globals.h"

void derive_graphics_metrics_from_loaded_level() {
    screen_width  = static_cast<float>(GetScreenWidth());
    screen_height = static_cast<float>(GetScreenHeight());

    cell_size = std::min(
            screen_width  / static_cast<float>(current_level.columns),
            screen_height / static_cast<float>(current_level.rows)
    ) * CELL_SCALE;
    screen_scale = std::min(
            screen_width,
            screen_height
    ) / SCREEN_SCALE_DIVISOR;
    float level_width  = static_cast<float>(current_level.columns) * cell_size;
    float level_height = static_cast<float>(current_level.rows)    * cell_size;
    shift_to_center_cell_by_x = (screen_width - level_width)   * 0.5f;
    shift_to_center_cell_by_y = (screen_height - level_height) * 0.5f;
}

void draw_level() {
    for (size_t row = 0; row < current_level.rows; ++row) {
        for (size_t column = 0; column < current_level.columns; ++column) {
            float x = shift_to_center_cell_by_x + static_cast<float>(column) * cell_size;
            float y = shift_to_center_cell_by_y + static_cast<float>(row) * cell_size;

            char cell = current_level.data[row * current_level.columns + column];
            switch (cell) {
                case WALL:
                    draw_image(wall_image, x, y, cell_size);
                    break;
                case COIN:
                    draw_image(coin_image, x, y, cell_size);
                    break;
                case EXIT:
                    draw_image(exit_image, x, y, cell_size);
                    break;
                default:
                    break;
            }
        }
    }

    draw_player();
}

void draw_player() {
    float x = shift_to_center_cell_by_x + player_pos.x * cell_size;
    float y = shift_to_center_cell_by_y + player_pos.y * cell_size;
    draw_sprite(player_sprite, x, y, cell_size);
}

#endif //GRAPHICS_H
