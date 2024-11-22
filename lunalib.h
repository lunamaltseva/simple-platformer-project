#ifndef LUNALIB_H
#define LUNALIB_H

#include "raylib.h"
#include <string>
#include <cstddef>
#include <utility>
#include <vector>
#include <functional>
#include <sstream>
#include <fstream>
#include <algorithm>
#include <chrono>

size_t game_frame = 0;
size_t runtime = 0;

bool mv_down() {
    return (IsKeyPressed(KEY_S) || IsKeyPressed(KEY_DOWN) || IsKeyPressed(KEY_D) || IsKeyPressed(KEY_RIGHT));
}

bool mv_up() {
    return (IsKeyPressed(KEY_W) || IsKeyPressed(KEY_UP) || IsKeyPressed(KEY_A) || IsKeyPressed(KEY_LEFT));
}

bool mv_forward() {
    return (IsKeyPressed(KEY_ENTER));
}

bool mv_back() {
    return (IsKeyPressed(KEY_ESCAPE));
}

int key_recently_pressed = 0;
bool is_key(int check) {
    return IsKeyDown(check) && key_recently_pressed == check;
}

Font menu_font;

class Text {
public:
    Text(const std::string text, Color color = WHITE, float size = 50.0f, Vector2 offset = {0.5f,0.5f}, float spacing = 4.0f, Font *font = &menu_font)
            : text(text), color(color), size(size), font(font), spacing(spacing), offsetPercent(offset) {}
    virtual void draw();
    void reposition(Vector2 position) {
        offsetPercent = position;
    }
protected:
    std::string text;
    float size, spacing;
    Vector2 offsetPercent, dimensions;
    Color color;
    Font* font;

    friend class Prompt;
};

class MultilineText : public Text {
public:
    MultilineText(const std::string text, Vector2 dOffset = {0.0f, 0.075f}, Color color = WHITE, float size = 50.0f, Vector2 offset = {0.5f,0.5f}, float spacing = 4.0f, Font *font = &menu_font)
            : Text("", color, size, offset, spacing, font), dOffset(dOffset) {
        std::stringstream stream(text);
        while (!stream.eof()) {
            std::string token;
            std::getline(stream, token, '\n');
            lines.push_back(token);
        }
    }
    void draw() override;
protected:
    Vector2 dOffset;
    std::vector<std::string> lines;

    friend class Prompt;
};

class Prompt {
public:
    Prompt(std::string title, std::string contents)
            : title(Text(title, WHITE, 70.0f)), contents(MultilineText(contents)) { }
    void draw();
private:
    Text title;
    MultilineText contents;
    Text OK = Text("OK", WHITE, 40.0f);
};

void drawImage(Texture2D image, float x, float y, float width, float height);

class Slide {
public:
    Slide(const std::string &text, const Texture2D picture)
            : caption{Text(text, WHITE, 70.0f, {0.5f, 0.9f})}, picture{picture} { }
    void draw() {
        caption.draw();
        float minimum = std::min(GetScreenHeight(), GetScreenWidth())*0.4f;
        drawImage(picture, (GetScreenWidth() - (2 * minimum)) * 0.5f, (GetScreenHeight() - minimum) * 0.5f, 2 * minimum, minimum);
    }
private:
    Text caption;
    Texture2D picture;
};

int animationFrame;

class Slideshow {
public:
    explicit Slideshow(int time) : timePerSlide(time) {}
    explicit Slideshow(std::vector<Slide> slides, int time) : slides(std::move(slides)), timePerSlide(time) {}
    void add(const Slide &slide) { slides.push_back(slide); }
    int at() {
        return itr;
    }

    bool draw() {
        if (itr >= slides.size()) {
            itr = 0;
            return false;
        }

        animationFrame++;

        slides[itr].draw();
        if (animationFrame > 0 && animationFrame < 45) {
            DrawRectangle(0, 0, GetScreenWidth(), GetScreenHeight(), {0,0,0, static_cast<unsigned char>(256-(animationFrame*(256.0f/45)))});
        }
        else if (animationFrame > timePerSlide-45 && animationFrame <= timePerSlide) {
            DrawRectangle(0, 0, GetScreenWidth(), GetScreenHeight(), {0,0,0, static_cast<unsigned char>(((animationFrame-(timePerSlide-45))*(250.0f/45)))});
        }

        if (animationFrame >= timePerSlide) {
            itr++;
            animationFrame = 0;
        }
        return true;
    }
private:
    int timePerSlide;
    int itr = 0;
    std::vector<Slide> slides;
};

struct vector2 {
    vector2() : x(0), y(0) {};
    vector2(size_t row, size_t column) : x(row), y(column) {}
    size_t x, y;
};

class Level {
public:
    static const char WALL   = '#',
                      AIR    = ' ',
                      PLAYER = '@',
                      COIN   = '$',
                      KEY    = '*',
                      EXIT   = 'E',
                      SPIKE  = '^',
                      ELECTRO= '<';

    Level() {}
    Level(size_t height, size_t width, char *data, long long allocated_time, size_t keys = 0)
            : rows(height), columns(width), data(data), allocated_time(allocated_time*60+59), keys(keys) { }

    char& get_cell(size_t row, size_t column);
    void set_cell(size_t row, size_t column, char cell);
    long long countdown() {allocated_time--; return time();}
    long long time() { return allocated_time; }

    [[nodiscard]] size_t height()     const { return rows;    }
    [[nodiscard]] size_t width()      const { return columns; }
    [[nodiscard]] size_t keys_total() const { return keys;    }
    friend class LevelManager;
protected:
    size_t rows, columns, keys;
    char *data;
    long long allocated_time;
};

struct levelStatistics {
    size_t steps;
    size_t time;
};

class LevelManager {
public:
    LevelManager();
    static void add(Level &level) {levels.push_back(level);}

    static Level* getInstance() {
        if (instance == nullptr)
            instance = new Level();
        return instance;
    }

    static void load(size_t offset = 0);
    static void unload();
    static void reset() { index = 0; }
    static void forceComplete();
    static size_t get_index() { return index; }
    static size_t get_size()  { return levels.size(); }
    static void draw();
    static std::vector<levelStatistics> stats;

    friend void tutorials();
private:
    static Level* instance;
    static size_t index;
    static std::vector<Level> levels;
};

Level* LevelManager::instance = nullptr;
size_t LevelManager::index = 0;
std::vector<Level> LevelManager::levels;
std::vector<levelStatistics> LevelManager::stats(3);

bool is_colliding(Vector2 pos, char look_for);

enum game_state {
    INTRO_STATE,
    MENU_STATE,
    GAME_STATE,
    PAUSED_STATE,
    YOU_DIED_STATE,
    GAME_OVER_STATE,
    OPTIONS_STATE,
    ENDING_STATE
};
game_state game_state = INTRO_STATE;

extern Sound death_sound;

class Player {
public:
    Player() { for(int i = 0; i < 10; i++) {coins.push_back(0); keys.push_back(0);}}
    void spawn(size_t row, size_t column);
    void move_horizontally(float delta);
    void update();
    bool is_player_on_ground() {
        is_in_air = is_colliding({pos.x, pos.y + 0.1f}, Level::WALL);
        return is_in_air;
    }
    void set_y_velocity(float v) { y_velocity = v; }
    void draw();
    void reset() {lives = 3; keys.clear(); coins.clear(); for(int i = 0; i < 10; i++) {coins.push_back(0); keys.push_back(0);}}
    void kill() {
        lives-=1;
        keys[LevelManager::get_index()] = 0;
        coins[LevelManager::get_index()] = 0;
        game_state = (lives <= 0 ? GAME_OVER_STATE : YOU_DIED_STATE);
        PlaySound(death_sound);
    };
    size_t get_lives() {return lives;}
    size_t get_coins() {size_t sum = 0; for (auto v : coins) sum+=v; return sum;}
    size_t get_keys()  {return keys[LevelManager::get_index()];}
    void lose_coins(size_t offset) {if (get_coins()>0) coins[LevelManager::get_index()] -= offset;}
private:
    Vector2 pos;
    float y_velocity;
    bool is_in_air, is_looking_forward, is_moving;
    size_t lives = 3;
    std::vector<size_t> coins;
    std::vector<size_t> keys;
};

struct Electro{
    float x, y;
    bool is_right = false;
};

bool is_colliding(Vector2 pos, char look_for);

class ElectroManager{
public:
    static void spawn(float x, float y) {
        arr.push_back({x, y});
    }
    static void reset() {
        arr.clear();
    }
    static void update() {
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
    static bool is_colliding_enemy(Vector2 pos);
    static void draw();
private:
    static std::vector<Electro> arr;
    const static float electro_speed;
};

const float ElectroManager::electro_speed = 0.05f;
std::vector<Electro> ElectroManager::arr;

struct Option {
    std::string text;
    std::function<void()> forward;
};

extern Sound scroll;
extern Sound forward;
extern Sound backout;

class Menu {
public:
    Menu(std::vector<Option> entry, std::function<void()> backward, Color colorActive = WHITE, Color colorInactive = GRAY, float size = 50.0f, Vector2 offset = {0.5f,0.5f}, Vector2 offsetAdd = {0.0f, 0.1f}, float spacing = 3.0f, Font *font = &menu_font)
            : entry(entry), backward(backward), colorActive(colorActive), colorInactive(colorInactive), size(size), font(font), spacing(spacing), offsetPercentInitial(offset), offsetPercentAdditional(offsetAdd), selection(0) {}
    void draw();
    void run();
    int selected() {return selection;}
protected:
    std::vector<Option> entry;
    std::function<void()> backward;
    int selection;
    float size, spacing;
    Vector2 offsetPercentInitial, offsetPercentAdditional;
    Color colorActive, colorInactive;
    Font* font;
};

void Menu::draw() {
    for (int i = 0; i < entry.size(); i++) {
        Text(entry[i].text, (i == selection ? colorActive : colorInactive), size, {offsetPercentInitial.x + offsetPercentAdditional.x*i, offsetPercentInitial.y + offsetPercentAdditional.y*i}, spacing, font).draw();
    }
}

void Menu::run() {
    if (mv_down())         {if (entry.size() <= ++selection) selection = 0; PlaySound(scroll);}
    else if (mv_up())      {if (0 > --selection) selection = entry.size()-1;PlaySound(scroll);}
    else if (mv_forward()) {entry[selection].forward();PlaySound(forward);}
    else if (mv_back())    {backward();PlaySound(backout);}
    this->draw();
}

struct Parameters {
    int value;
    enum values {key, speed};
    values valueType;
};

class OptionsMenu : public Menu {
public:
    OptionsMenu(std::vector<Option> entry, std::function<void()> backward, Color colorActive = WHITE, Color colorInactive = GRAY, float size = 50.0f, Vector2 offset = {0.5f,0.5f}, Vector2 offsetAdd = {0.0f, 0.1f}, float spacing = 4.0f, Font *font = &menu_font)
            : Menu(entry, backward, colorActive, colorInactive, size, offset, offsetAdd, spacing, font) {}

    void draw();
    int getKey();
    void increaseDecrease();
    void run();

    char getChar(int index) {
        return static_cast<char>(parameters[index].value);
    }

    int getValue(int index) {
        return parameters[index].value;
    }
protected:
    std::vector<Parameters> parameters = {{KEY_W, Parameters::key},{KEY_A, Parameters::key}, {KEY_D, Parameters::key}};
    bool selected;
    float offset = 0.53f;
};

int OptionsMenu::getKey() {
    int stroke = GetKeyPressed();
    if (stroke != 0) {
        parameters[selection].value = stroke;
    }
    return parameters[selection].value;
}

void OptionsMenu::increaseDecrease() {
    int &val = parameters[selection].value;

    if (val>=1 && val<=60) {
        if (mv_down() && val!=60) val++;
        else if (mv_up() && val!=1) val--;
    }
}

void OptionsMenu::run() {
    if (!selected) {
        if (mv_back()) { backward(); PlaySound(backout); }
        else if (mv_forward()) {selected = true; PlaySound(forward);}
        else if (mv_down()) { if (entry.size() <= ++selection) selection = 0; PlaySound(scroll);}
        else if (mv_up()) { if (0 > --selection) selection = entry.size() - 1; PlaySound(scroll);}
    }
    else {
        if (mv_back() || mv_forward()) {selected = false; PlaySound(backout);}
        else {
            entry[selection].forward();
        }
    }

    this->draw();
}

void OptionsMenu::draw() {
    Menu::draw();
    for (int i = 0; i < entry.size(); i++) {
        Text(parameters[i].valueType == Parameters::speed ? std::to_string(parameters[i].value) : std::string(1, static_cast<char>(parameters[i].value)), (i == selection && selected ? colorActive : colorInactive), size, {offset + offsetPercentAdditional.x*i, offsetPercentInitial.y + offsetPercentAdditional.y*i}, spacing, font).draw();;
    }
}

#endif //LUNALIB_H