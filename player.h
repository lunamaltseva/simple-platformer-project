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
    else {
        pos.x = roundf(pos.x);
        is_looking_forward = delta > 0;
    }
}

void Player::update() {
    update_gravity();

    if (is_colliding(pos, Level::COIN)) {
        get_collider(pos, Level::COIN) = ' ';
        coins[LevelManager::get_index()]++;
        PlaySound(coin_sound);
    }
    else if (is_colliding(pos, Level::KEY)) {
        get_collider(pos, Level::KEY) = ' ';
        keys[LevelManager::get_index()]++;
        PlaySound(key_sound);
    }
    else if (is_colliding(pos, Level::EXIT)) {
        if (LevelManager::getInstance()->keys_total() <= keys[LevelManager::get_index()]) {
            LevelManager::load(1);
            PlaySound(exit_sound);
        }
    }
    else if (is_colliding(pos, Level::SPIKE)) {
        player.kill();
    }

    if (ElectroManager::is_colliding_enemy(pos)) {
        player.kill();
    }
}

void Player::update_gravity() {
    if (is_colliding({pos.x, pos.y - 0.1f}, Level::WALL) && y_velocity < 0) {
        y_velocity = 0.05;
    }

    pos.y += y_velocity;
    y_velocity += GRAVITY_FORCE;

    is_in_air = !is_colliding({pos.x, pos.y + 0.1f}, Level::WALL);
    if (!is_in_air) {
        y_velocity = 0;
        pos.y = roundf(pos.y);
    }
}

bool Player::is_player_on_ground() {
    is_in_air = is_colliding({pos.x, pos.y + 0.1f}, Level::WALL);
    return is_in_air;
}

void Player::kill() {
    lives-=1;
    keys[LevelManager::get_index()] = 0;
    coins[LevelManager::get_index()] = 0;
    game_state = YOU_DIED_STATE;
    PlaySound(death_sound);
}

void Player::respawn() {
    keys[LevelManager::get_index()] = 0;
    coins[LevelManager::get_index()] = 0;
};

#endif //PLAYER_H
