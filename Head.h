#ifndef SNAKE_HEAD_H
#define SNAKE_HEAD_H

#include "Body.h"
#include "Difficulty.h"

class Head : public Body{
private:
    int i_direction;
    int p_direction;
    int speed;

public:
    Head(int X_pos, int Y_pos, sf::Texture *texture, sf::RenderWindow *window, Difficulty diff);
    void Update(float deltaTime) override;
    bool checkCollision(Entity *entity);
};

#endif