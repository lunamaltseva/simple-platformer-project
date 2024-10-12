#ifndef LEVEL_H
#define LEVEL_H

#include "globals.h"

void load_level(int offset = 0) {
    level_index += offset;
    current_level = LEVELS[level_index];

    spawn_player();
    derive_graphics_metrics_from_loaded_level();
}

#endif //LEVEL_H
