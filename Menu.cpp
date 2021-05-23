#include "Menu.h"

Menu::Menu(sf::RenderWindow* window){
    start_game = new Button(700, 325, 130, 50, sf::Color(128, 128, 128), "NEW GAME", window);
    high_scores = new Button(700, 400, 130, 50, sf::Color(128, 128, 128), "SCORES", window);
    difficulties = new Button(700, 475, 130, 50, sf::Color(128, 128, 128), "LEVEL", window);
    difficulties_easy = new Button(700, 325, 130, 50, sf::Color(128, 128, 128), "EASY", window);
    difficulties_normal = new Button(700, 400, 130, 50, sf::Color(128, 128, 128), "NORMAL", window);
    difficulties_hard= new Button(700, 475, 130, 50, sf::Color(128, 128, 128), "HARD", window);
    back = new Button(700, 550, 130, 50, sf::Color(128, 128, 128), "BACK", window);
    quit = new Button(700, 550, 130, 50, sf::Color(128, 128, 128), "QUIT", window);
}

Menu::~Menu(){
    delete start_game;
    delete high_scores;
    delete difficulties;
    delete difficulties_easy;
    delete difficulties_normal;
    delete difficulties_hard;
    delete back;
    delete quit;
}

void Menu::Update(){

}

void Menu::Draw(){
    if(!inScoreView && !inDifficultyView){
        start_game->Draw();
        high_scores->Draw();
        difficulties->Draw();
        quit->Draw();
    }else{
        if(inDifficultyView){
            difficulties_easy->Draw();
            difficulties_normal->Draw();
            difficulties_hard->Draw();
        }
        back->Draw();
    }
}

void Menu::CheckButtonPresses(sf::Event::MouseButtonEvent *mouse_event){
    if(inDifficultyView){
        if(difficulties_easy->isButtonPressed(mouse_event)){
            selected_difficulty = EASY;
            inDifficultyView = false;
        }
        if(difficulties_normal->isButtonPressed(mouse_event)){
            selected_difficulty = NORMAL;
            inDifficultyView = false;
        }
        if(difficulties_hard->isButtonPressed(mouse_event)){
            selected_difficulty = HARD;
            inDifficultyView = false;
        }
    }
    if(!inScoreView && !inDifficultyView){
        if(start_game->isButtonPressed(mouse_event)){
            start_game_requested = true;
        }
        if(high_scores->isButtonPressed(mouse_event)){
            inScoreView = true;
        }
        if(difficulties->isButtonPressed(mouse_event)){
            inDifficultyView = true;
        }
        if(quit->isButtonPressed(mouse_event)){
            quit_requested = true;
        }
    }
    if(back->isButtonPressed(mouse_event)){
        inScoreView = false;
        inDifficultyView = false;
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