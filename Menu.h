#ifndef SNAKE_MENU_H
#define SNAKE_MENU_H

#include "Button.h"

class Menu{
private:
    Button* start_game;
    Button* high_scores;
    Button* back;
    Button* quit;
    bool start_game_requested, quit_requested;
    bool inScoreView;

public:
    Menu(sf::RenderWindow* window);
    ~Menu();
    void Update();
    void Draw();
    void CheckButtonPresses(sf::Event::MouseButtonEvent* mouse_event);
    bool RequestedQuit();
    bool RequestedStartGame();
};


#endif