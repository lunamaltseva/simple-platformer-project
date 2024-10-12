#ifndef UTILITIES_H
#define UTILITIES_H

#include <cstdlib>
#include "raylib.h"

bool is_colliding_object(float x, float y, char lookOut = '#', level &level = current_level) {
    const float size = 1;
    Rectangle a = {x, y, size, size};

    for (size_t row = 0; row < level.rows; ++row) {
        for (size_t column = 0; column < level.columns; ++column) {
            if (level.data[row * level.columns + column] == lookOut) {
                Rectangle b = {(float) column, (float) row, (float) size, (float) size};
                if (CheckCollisionRecs(a, b))
                    return true;
            }
        }
    }
    return false;
}

char& get_colliding_object(float x, float y, char lookOut, level &level = current_level) {
    const float size = 1;
    Rectangle a = {x, y, size, size};

    for (size_t row = 0; row < level.rows; ++row) {
        for (size_t column = 0; column < level.columns; ++column) {
            if (level.data[row * level.columns + column] == lookOut) {
                Rectangle b = {(float) column, (float) row, (float) size, (float) size};
                if (CheckCollisionRecs(a, b))
                    return level.data[row * level.columns + column];
            }
        }
    }
}

float rand_from_to(float from, float to) {
    return from + static_cast<float>(std::rand()) / static_cast<float>(RAND_MAX) * (to - from); // NOLINT(*-msc50-cpp)
}

float rand_up_to(float to) {
    return rand_from_to(0.0f, to);
}

#endif // UTILITIES_H
