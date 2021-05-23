#ifndef SNAKE_BUTTON_H
#define SNAKE_BUTTON_H

#include <SFML/Graphics.hpp>
#include <ostream>

class Button{
private:
    sf::RectangleShape* button_shape;
    sf::Text* text;
    sf::RenderWindow* window;
    sf::Font* font;

public:
    Button(int x_pos, int y_pos, int width, int height, sf::Color color, std::string, sf::RenderWindow* window);
    ~Button();
    bool isButtonPressed(sf::Event::MouseButtonEvent* mouse_event) const;
    void Draw();
};

#endif