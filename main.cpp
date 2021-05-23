#include "Game.h"

int main(){

    Game* game = new Game(HARD);
    game->Init();

    while(game->isWindowOpen()){
        game->Update();
        game->DebugView();
        game->Draw();
    }

    delete game;

    return 0;
}