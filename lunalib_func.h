#ifndef LUNALIB_FUNC_H
#define LUNALIB_FUNC_H

#include "lunalib.h"
#include "globals.h"

/* Text */

Text::Text(const std::string text, Color color, float size, Vector2 offset, float spacing, Font *font)
        : text(text), color(color), size(size), font(font), spacing(spacing), offsetPercent(offset) {}

void Text::draw() {
    dimensions = MeasureTextEx(*font, text.c_str(), size*((float)GetScreenHeight()/1080), spacing);

    Vector2 pos = {
            (screen_size.x * offsetPercent.x) - (0.5f * dimensions.x),
            (screen_size.y * offsetPercent.y) - (0.5f * dimensions.y)
    };
    DrawTextEx(*font, text.c_str(), pos, dimensions.y, spacing, color);
}

void Text::reposition(Vector2 position) {
    offsetPercent = position;
}

/* Multiline text */

MultilineText::MultilineText(const std::string text, Vector2 dOffset, Color color, float size, Vector2 offset, float spacing, Font *font)
    : Text("", color, size, offset, spacing, font), dOffset(dOffset) {
    std::stringstream stream(text);
    while (!stream.eof()) {
        std::string token;
        std::getline(stream, token, '\n');
        lines.push_back(token);
    }
}

void MultilineText::draw() {
    for (int i = 0; i < lines.size(); i++) {
        Text(lines[i], color, size, {offsetPercent.x+dOffset.x*i, offsetPercent.y+dOffset.y*i}, spacing, font).draw();
    }
}

/* Prompt */

Prompt::Prompt(std::string title, std::string contents)
    : title(Text(title, WHITE, 70.0f)), contents(MultilineText(contents)) { }

void Prompt::draw() {
    Vector2 size = {0,0};
    size.y = title.size +(contents.dOffset.y * screen_size.y * static_cast<float>(contents.lines.size()));
    for (auto &el : contents.lines) {
        if (MeasureTextEx(*contents.font, el.c_str(), contents.size, contents.spacing).x > size.x)
            size.x = MeasureTextEx(*contents.font, el.c_str(), contents.size, contents.spacing).x;
    }
    Vector2 sizePercent = {((screen_size.x - size.x) * 0.5f) / screen_size.x, ((screen_size.y - size.y) * 0.5f) / screen_size.y};
    title.reposition({0.5f, sizePercent.y});
    contents.reposition({0.5f, sizePercent.y + ((title.size + 30.0f) / screen_size.y)});
    OK.reposition({0.5f, ((size.y + screen_size.y) * 0.52f) / screen_size.y});

    DrawRectangle((screen_size.x - size.x) * 0.5f - 80.0f, (screen_size.y - size.y) * 0.5f - 80.0f, size.x + 160.0f, size.y + 160.0f, BLACK);
    DrawRectangleLinesEx({(screen_size.x - size.x) * 0.5f - 80.0f, (screen_size.y - size.y) * 0.5f - 80.0f, size.x + 160.0f, size.y + 160.0f}, 5.0f, WHITE);

    title.draw();
    contents.draw();
    OK.draw();
}

/* Slide */

Slide::Slide(const std::string &text, const Texture2D picture)
        : caption{Text(text, WHITE, 70.0f, {0.5f, 0.9f})}, picture{picture} { }

void Slide::draw() {
    caption.draw();
    float minimum = std::min(GetScreenHeight(), GetScreenWidth())*0.4f;
    draw_image(picture, {(GetScreenWidth() - (2 * minimum)) * 0.5f, (GetScreenHeight() - minimum) * 0.5f}, 2 * minimum, minimum);
}

/* Slideshow */

Slideshow::Slideshow(int time)
    : timePerSlide(time) {}
Slideshow::Slideshow(std::vector<Slide> slides, int time)
    : slides(std::move(slides)), timePerSlide(time) {}

void  Slideshow::add(const Slide &slide) {
    slides.push_back(slide);
}

int Slideshow::at() {
    return itr;
}

bool Slideshow::draw() {
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

/* Level */

Level::Level(size_t height, size_t width, char *data, long long allocated_time, size_t keys)
    : rows(height), columns(width), data(data), allocated_time(allocated_time*60+59), keys(keys) { }

char& Level::get_cell(size_t row, size_t column) {
    return data[row * columns + column];
}

void Level::set_cell(size_t row, size_t column, char cell) {
    data[row * columns + column] = cell;
}

/* Menu */

Menu::Menu(std::vector<Option> entry, std::function<void()> backward, Color colorActive, Color colorInactive, float size, Vector2 offset, Vector2 offsetAdd, float spacing, Font *font)
    : entry(entry), backward(backward), colorActive(colorActive), colorInactive(colorInactive), size(size), font(font), spacing(spacing), offsetPercentInitial(offset), offsetPercentAdditional(offsetAdd), selection(0) {}

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

/* Options Menu */

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

#endif //LUNALIB_FUNC_H
