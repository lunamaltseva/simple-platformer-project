#ifndef IMAGES_H
#define IMAGES_H

#include "raylib.h"
#include "globals.h"

#include <string>
#include <cassert>

void load_fonts() {
    menu_font = LoadFontEx("data/fonts/alagard.ttf", 256, nullptr, 128);
}

void unload_fonts() {
    UnloadFont(menu_font);
}

void load_images() {
    wall_image                      = LoadTexture("data/images/wall.png");
    air_image                       = LoadTexture("data/images/air.png");
    exit_no_keys                    = LoadTexture("data/images/exit_no_keys.png");
    exit_keys_closed                = LoadTexture("data/images/exit_closed.png");
    exit_keys_open                  = LoadTexture("data/images/exit_open.png");
    heart_image                     = LoadTexture("data/images/heart.png");
    spike_image                     = LoadTexture("data/images/spikes.png");
    coin_sprite                     = load_sprite("data/images/coin/coin", ".png", 3, true, 18);
    key_sprite                      = load_sprite("data/images/key/key", ".png", 4, true, 18);
    key_image                       = LoadTexture("data/images/key.png");
    key_outline_image               = LoadTexture("data/images/key_outline.png");
    ability_image                   = LoadTexture("data/images/double_jump.png");
    player_stand_forward_image      = LoadTexture("data/images/player_stand_forward.png");
    player_stand_backwards_image    = LoadTexture("data/images/player_stand_backwards.png");
    player_jump_forward_image       = LoadTexture("data/images/player_jump_forward.png");
    player_jump_backwards_image     = LoadTexture("data/images/player_jump_backwards.png");
    player_dead_image               = LoadTexture("data/images/player_dead.png");
    player_walk_forward_sprite      = load_sprite("data/images/player_walk_forward/player", ".png", 3, true, 15);
    player_walk_backwards_sprite    = load_sprite("data/images/player_walk_backwards/player", ".png", 3, true, 15);
    electro_sprite                  = load_sprite("data/images/electro/electro", ".png", 3, true, 9);

    intro1              = LoadTexture("data/images/slides/intro1.png");
    intro2              = LoadTexture("data/images/slides/intro2.png");
    intro3              = LoadTexture("data/images/slides/intro3.png");
    intro4              = LoadTexture("data/images/slides/intro4.png");
    ending1             = LoadTexture("data/images/slides/final1.png");
    ending2             = LoadTexture("data/images/slides/final2.png");
    ending3             = LoadTexture("data/images/slides/final3.png");

    intro.add({"I used to live to my fullest.",       intro1});
    intro.add({"Nowadays?... Not so much.",           intro2});
    intro.add({"But my days are numbered...",         intro3});
    intro.add({"And I can't go out without a blaze.", intro4});

    ending.add({"Almost there...", ending1});
    ending.add({"I...",            ending2});
    ending.add({"...",             ending3});
}

void unload_images() {
    UnloadTexture(wall_image);
    UnloadTexture(air_image);
    UnloadTexture(exit_no_keys);
    unload_sprite(coin_sprite);
}

void drawImage(Texture2D image, float x, float y, float width, float height) {
    draw_image(image, {x, y}, width, height);
}

void draw_image(Texture2D image, Vector2 pos, float size) {
    draw_image(image, pos, size, size);
}

void draw_image(Texture2D image, Vector2 pos, float width, float height) {
    Rectangle source = { 0.0f, 0.0f, static_cast<float>(image.width), static_cast<float>(image.height) };
    Rectangle destination = { pos.x, pos.y, width, height };
    DrawTexturePro(image, source, destination, { 0.0f, 0.0f }, 0.0f, WHITE);
}

sprite load_sprite(
    const std::string &file_name_prefix,
    const std::string &file_name_suffix,
    size_t frame_count,
    bool loop,
    size_t frames_to_skip
) {
    assert(frame_count < 100);

    sprite result = {
        frame_count, frames_to_skip, 0, 0, loop, 0, new Texture2D[frame_count]
    };

    for (size_t i = 0; i < frame_count; ++i) {
        std::string file_name;
        if (frame_count < 10) {
            file_name = file_name_prefix;
            file_name += std::to_string(i);
            file_name += file_name_suffix;
        } else {
            file_name = file_name_prefix;
            file_name += i < 10 ? ("0" + std::to_string(i)) : std::to_string(i);
            file_name += file_name_suffix;
        }
        result.frames[i] = LoadTexture(file_name.c_str());
    }

    return result;
}

void unload_sprite(sprite &sprite) {
    assert(sprite.frames != nullptr);

    for (size_t i = 0; i < sprite.frame_count; ++i) {
        UnloadTexture(sprite.frames[i]);
    }
    delete[] sprite.frames;
    sprite.frames = nullptr;
}

void draw_sprite(sprite &sprite, Vector2 pos, float size) {
    draw_sprite(sprite, pos, size, size);
}

void draw_sprite(sprite &sprite, Vector2 pos, float width, float height) {
    draw_image(sprite.frames[sprite.frame_index], pos, width, height);

    if (sprite.prev_game_frame == game_frame) {
        return;
    }
    if (sprite.frames_skipped < sprite.frames_to_skip) {
        ++sprite.frames_skipped;
    } else {
        sprite.frames_skipped = 0;

        ++sprite.frame_index;
        if (sprite.frame_index >= sprite.frame_count) {
            sprite.frame_index = sprite.loop ? 0 : sprite.frame_count - 1;
        }
    }
    sprite.prev_game_frame = game_frame;
}

void load_sounds() {
    scroll         = LoadSound("data/sounds/scroll.ogg");
    forward        = LoadSound("data/sounds/click.ogg");
    backout        = LoadSound("data/sounds/backout.ogg");

    coin_sound     = LoadSound("data/sounds/coin.wav");
    exit_sound     = LoadSound("data/sounds/exit.wav");
    death_sound    = LoadSound("data/sounds/death.ogg");
    key_sound      = LoadSound("data/sounds/key.ogg");
    air_jump_sound = LoadSound("data/sounds/air_jump.ogg");

    theme          = LoadMusicStream("data/music/theme.ogg");
    main_theme     = LoadMusicStream("data/music/main.ogg");
    game           = LoadMusicStream("data/music/game.ogg");
    idle           = LoadMusicStream("data/music/idle.ogg");
}

void unload_sounds() {
    UnloadSound(coin_sound);
    UnloadSound(exit_sound);
}

void play(Sound sound) {
    PlaySound(sound);
}

void play(Music music) {
    PlayMusicStream(music);
    UpdateMusicStream(music);
}

#endif // IMAGES_H
