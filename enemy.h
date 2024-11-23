#ifndef ENEMY_H
#define ENEMY_H

#include "globals.h"

void ElectroManager::spawn(float x, float y) {
    arr.push_back({x, y});
}
void ElectroManager::reset() {
    arr.clear();
}
void ElectroManager::update() {
    for (auto &electro : arr) {
        if (electro.is_right) {
            electro.x += electro_speed;
            float next_x = electro.x + electro_speed;
            if (is_colliding({next_x, electro.y}, Level::WALL)) {
                electro.is_right = false;
            }
        }
        else {
            electro.x -= electro_speed;
            float next_x = electro.x - electro_speed;
            if (is_colliding({next_x, electro.y}, Level::WALL)) {
                electro.is_right = true;
            }
        }
    }
}

bool ElectroManager::is_colliding_enemy(Vector2 pos) {
    Rectangle player_hitbox = {pos.x, pos.y, 1.0f, 1.0f};

    for (auto electro : arr) {
        Rectangle enemy_hitbox = {electro.x, electro.y, 1.0f, 1.0f};
        if (CheckCollisionRecs(player_hitbox, enemy_hitbox)) {
            return true;
        }
    }
    return false;
}

#endif //ENEMY_H
