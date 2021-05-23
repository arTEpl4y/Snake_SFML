#include "Menu.h"

Menu::Menu(sf::RenderWindow* window){
    font = new sf::Font;
    font->loadFromFile("../arial.ttf");

    start_game = new Button(700, 325, 130, 50, sf::Color(128, 128, 128), "NEW GAME", font, window);
    high_scores = new Button(700, 400, 130, 50, sf::Color(128, 128, 128), "SCORES", font, window);
    difficulties = new Button(700, 475, 130, 50, sf::Color(128, 128, 128), "LEVEL", font, window);
    difficulties_easy = new Button(700, 325, 130, 50, sf::Color(128, 128, 128), "EASY", font, window);
    difficulties_normal = new Button(700, 400, 130, 50, sf::Color(128, 128, 128), "NORMAL", font, window);
    difficulties_hard= new Button(700, 475, 130, 50, sf::Color(128, 128, 128), "HARD", font, window);
    back = new Button(700, 550, 130, 50, sf::Color(128, 128, 128), "BACK", font, window);
    quit = new Button(700, 550, 130, 50, sf::Color(128, 128, 128), "QUIT", font, window);
    fps_counter = new sf::Text("0", *font, 12);
    fps_counter->setOrigin(fps_counter->getGlobalBounds().width/2, fps_counter->getGlobalBounds().height/2+3);
    fps_counter->setPosition(785, 590);

    this->window = window;
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
    delete fps_counter;
    delete font;
}

void Menu::UpdateFPS(float deltaTime){
    fps_counter->setString(std::to_string((int)((1/deltaTime))));
}

void Menu::Draw(){
    if(inDifficultyView){
        difficulties_easy->Draw();
        difficulties_normal->Draw();
        difficulties_hard->Draw();
    }
    if(!inScoreView && !inDifficultyView){
        start_game->Draw();
        high_scores->Draw();
        difficulties->Draw();
        quit->Draw();
    }else{
        back->Draw();
    }
    window->draw(*fps_counter);
}

void Menu::CheckButtonPresses(sf::Event::MouseButtonEvent *mouse_event){
    if(inDifficultyView){
        if(difficulties_easy->isButtonPressed(mouse_event)){
            selected_difficulty = EASY;
            inDifficultyView = false;
            return;
        }
        if(difficulties_normal->isButtonPressed(mouse_event)){
            selected_difficulty = NORMAL;
            inDifficultyView = false;
            return;
        }
        if(difficulties_hard->isButtonPressed(mouse_event)){
            selected_difficulty = HARD;
            inDifficultyView = false;
            return;
        }
    }
    if(!inScoreView && !inDifficultyView){
        if(start_game->isButtonPressed(mouse_event)){
            start_game_requested = true;
            return;
        }
        if(high_scores->isButtonPressed(mouse_event)){
            inScoreView = true;
            return;
        }
        if(difficulties->isButtonPressed(mouse_event)){
            inDifficultyView = true;
            return;
        }
        if(quit->isButtonPressed(mouse_event)){
            quit_requested = true;
            return;
        }
    }
    if(inScoreView || inDifficultyView){
        if(back->isButtonPressed(mouse_event)){
            inScoreView = false;
            inDifficultyView = false;
            return;
        }
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