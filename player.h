#ifndef PLAYER_H
#define PLAYER_H

#include "globals.h"

void Player::spawn(size_t row, size_t column) {
    pos.x = column;
    pos.y = row;
}

void Player::move_horizontally(float delta) {
    float next_x = pos.x + delta;
    if (!is_colliding({next_x, pos.y}, Level::WALL)) {
        pos.x = next_x;
        is_looking_forward = delta > 0;
        is_moving = true;
    }
    else
        pos.x = roundf(pos.x);
}

void Player::update() {
    // In THIS very order: first add velocity to position, then gravity to velocity
    // Why? I don't know! But it is glitchy otherwise.
    if (is_colliding({pos.x, pos.y - 0.1f}, Level::WALL) && y_velocity < 0) {
        y_velocity = 0.05;
    }
    pos.y += y_velocity;
    y_velocity += GRAVITY_FORCE;

    // Calculating collisions to see if the player hit the ceiling
    is_in_air = !is_colliding({pos.x, pos.y + 0.1f}, Level::WALL);
    if (!is_in_air) {
        y_velocity = 0;
        pos.y = roundf(pos.y);
    }

    // Interacting with other level elements
    if (is_colliding(pos, Level::COIN)) {
        get_collider(pos, Level::COIN) = ' '; // Remove the coin
        player_score+=10;
        PlaySound(coin_sound);
    }
    if (is_colliding(pos, Level::EXIT)) {
        LevelManager::load(1);
        PlaySound(exit_sound);
    }
}

#endif //PLAYER_H
