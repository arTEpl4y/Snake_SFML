#include <iostream>

#include "Body.h"

Body::Body(int X_pos, int Y_pos, sf::Texture *texture, sf::RenderWindow *window, Body* prev)
    :Entity(X_pos, Y_pos, texture, window){
    this->kimi_no_na_wa = prev;
}

void Body::Update(float deltaTime) {
    if (kimi_no_na_wa != nullptr && kimi_no_na_wa->history.size() >= 20) {
        history.emplace_back(point);
        if (history.size() > 20) {
            history.pop_front();
        }
        point.X = kimi_no_na_wa->history.front().X;
        point.Y = kimi_no_na_wa->history.front().Y;
        sprite.setPosition(point.X, point.Y);
    }
}