#include "Menu.h"

Menu::Menu(sf::RenderWindow* window){
    start_game_requested = false;
    quit_requested = false;

    start_game = new Button(700, 400, 130, 50, sf::Color(128, 128, 128), "NEW GAME", window);
    high_scores = new Button(700, 475, 130, 50, sf::Color(128, 128, 128), "SCORES", window);
    quit = new Button(700, 550, 130, 50, sf::Color(128, 128, 128), "QUIT", window);
    back = new Button(700, 550, 130, 50, sf::Color(128, 128, 128), "BACK", window);
}

Menu::~Menu(){
    delete start_game;
    delete high_scores;
    delete back;
    delete quit;
}

void Menu::Update(){

}

void Menu::Draw(){
    if(!inScoreView){
        start_game->Draw();
        high_scores->Draw();
        quit->Draw();
    }else{
        back->Draw();
    }
}

void Menu::CheckButtonPresses(sf::Event::MouseButtonEvent *mouse_event){
    if(!inScoreView){
        if(quit->isButtonPressed(mouse_event)){
            quit_requested = true;
        }
    }
    if(start_game->isButtonPressed(mouse_event)){
        start_game_requested = true;
    }
    if(high_scores->isButtonPressed(mouse_event)){
        inScoreView = true;
    }
    if(back->isButtonPressed(mouse_event)){
        inScoreView = false;
    }
}

bool Menu::RequestedQuit() {
    return quit_requested;
}

bool Menu::RequestedStartGame() {
    if(start_game_requested){
        start_game_requested = false;
        return true;
    }
    return false;
}