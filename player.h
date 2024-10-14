#ifndef PLAYER_H
#define PLAYER_H

#include "globals.h"

void spawn_player() {
    for (size_t row = 0; row < current_level.rows; ++row) {
        for (size_t column = 0; column < current_level.columns; ++column) {
            char cell = current_level.data[row * current_level.columns + column];

            if (cell == PLAYER) {
                player_pos.x = column;
                player_pos.y = row;
                return;
            }
        }
    }
}

void move_player_horizontally(float delta) {
    float next_x = player_pos.x + delta;
    if (!is_colliding({next_x, player_pos.y}, WALL))
        player_pos.x = next_x;
}

void update_player() {
    player_pos.y += player_y_velocity;
    player_y_velocity += gravity;

    bool is_player_on_ground = is_colliding({player_pos.x, player_pos.y + 0.1f}, WALL);
    if (is_player_on_ground) {
        player_y_velocity = 0;
        player_pos.y = roundf(player_pos.y);
    }

    bool is_player_in_wall = is_colliding({player_pos.x, player_pos.y}, WALL);
    if (is_player_in_wall) {
        player_pos.x = roundf(player_pos.x);
    }

    if (is_colliding(player_pos, COIN)) {
        get_collider(player_pos, COIN) = ' ';
    }
    if (is_colliding(player_pos, EXIT)) {
        load_level(1);
    }
}

#endif //PLAYER_H
