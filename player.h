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
    else
        player_pos.x = roundf(player_pos.x);
}

void update_player() {
    if (is_colliding({player_pos.x, player_pos.y - 0.1f}, WALL) && player_y_velocity < 0) {
        player_y_velocity = 0.05;
    }

    // In THIS very order: first add velocity to position, then gravity to velocity
    // Why? I don't know! But it is glitchy otherwise.
    player_pos.y += player_y_velocity;
    player_y_velocity += GRAVITY_FORCE;

    // Calculating collisions to see if the player hit the ceiling
    is_player_on_ground = is_colliding({player_pos.x, player_pos.y + 0.1f}, WALL);
    if (is_player_on_ground) {
        player_y_velocity = 0;
        player_pos.y = roundf(player_pos.y);
    }

    // Interacting with other level elements
    if (is_colliding(player_pos, COIN)) {
        get_collider(player_pos, COIN) = ' '; // Remove the coin
        player_score+=10;
        PlaySound(coin_sound);
    }
    if (is_colliding(player_pos, EXIT)) {
        load_level(1);
        PlaySound(exit_sound);
    }
}

#endif //PLAYER_H
