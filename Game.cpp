#include "Game.h"

Game::Game(Difficulty diff){
    srand(time(NULL));

    difficulty = diff;
}

Game::~Game(){
    delete menu;
    Stop();
    delete window;
}

void Game::DebugView() const{
    if(isGameRunning){
        std::cout << "FPS: " << 1/deltaTime << std::endl;
    }
}

void Game::Init(){
    head_t.loadFromFile("../Textures/head.png");
    body_t.loadFromFile("../Textures/body.png");
    food_t.loadFromFile("../Textures/food.png");

    wall_top = sf::RectangleShape(sf::Vector2f(600, 12));
    wall_top.setFillColor(sf::Color(128, 128, 128));
    wall_top.setPosition(0, 0);
    wall_right = sf::RectangleShape(sf::Vector2f(12, 600));
    wall_right.setFillColor(sf::Color(128, 128, 128));
    wall_right.setPosition(588, 0);
    wall_bottom = sf::RectangleShape(sf::Vector2f(600, 12));
    wall_bottom.setFillColor(sf::Color(128, 128, 128));
    wall_bottom.setPosition(0, 588);
    wall_left = sf::RectangleShape(sf::Vector2f(12, 600));
    wall_left.setFillColor(sf::Color(128, 128, 128));
    wall_left.setPosition(0, 0);

    window = new sf::RenderWindow(sf::VideoMode(800, 600), "Snake", sf::Style::Close | sf::Style::Resize);
    window->setFramerateLimit(30);

    menu = new Menu(window);

    isGameRunning = false;

    current_time = getMilliseconds();
    endOfFrameTime = getMilliseconds();
}

void Game::Update(){
    endOfFrameTime = getMilliseconds();
    deltaTime = (endOfFrameTime-current_time).count()*0.001;
    current_time = getMilliseconds();

    sf::Event event{};
    while(window->pollEvent(event)){
        switch(event.type){
            case sf::Event::Closed:
                window->close();
                break;
            case sf::Event::Resized:
                std::cout << event.size.width << " " << event.size.height << std::endl;
                break;
            case sf::Event::MouseButtonPressed:
                if(event.mouseButton.button==sf::Mouse::Left){
                    menu->CheckButtonPresses(&event.mouseButton);
                }
                break;
            default:
                break;
        }
    }
    if(sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Escape) || menu->RequestedQuit()){
        window->close();
    }
    if(menu->RequestedStartGame()){
        Stop();
        StartGame();
    }

    if(isGameRunning){
        head->Update(deltaTime);
        for(auto i:body_vec){
            i->Update(deltaTime);
            if(i->kimi_no_na_wa != head && head->checkCollision(i)){
                Stop();
            }
        }

        for(auto i:food_vec){
            if(head->checkCollision(i)){
                i->Spawn();
                if(body_vec.size() == 0){
                    body_vec.push_back(new Body(head->GetEntityX_pos(), head->GetEntityY_pos(), &body_t, window, head));
                }else{
                    body_vec.push_back(new Body(body_vec[body_vec.size()-1]->GetEntityX_pos(), body_vec[body_vec.size
                                                        ()-1]->GetEntityY_pos(), &body_t,
                                                window, body_vec[body_vec.size()-1]));
                }
                //add score
            }
        }

        a++;
        if(a >= 20 && b > 0){
            a = 0;
            b--;
            if(body_vec.size() == 0){
                body_vec.push_back(new Body(head->GetEntityX_pos(), head->GetEntityY_pos(), &body_t, window, head));
            }else{
                body_vec.push_back(new Body(body_vec[body_vec.size()-1]->GetEntityX_pos(), body_vec[body_vec.size
                                                    ()-1]->GetEntityY_pos(), &body_t,
                                            window, body_vec[body_vec.size()-1]));
            }
        }
    }
}

void Game::Draw(){
    window->clear(sf::Color(64, 64, 64));
    menu->Draw();
    window->draw(wall_top);
    window->draw(wall_right);
    window->draw(wall_bottom);
    window->draw(wall_left);
    if(isGameRunning){
        for(unsigned int i = 0; i < food_vec.size(); i++){
            food_vec[i]->Draw();
        }
        head->Draw();
        for(unsigned int i = 0; i < body_vec.size(); i++){
            body_vec[i]->Draw();
        }
    }
    window->display();
}

bool Game::isWindowOpen(){
    return window->isOpen();
}

std::chrono::milliseconds Game::getMilliseconds(){
    return std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::system_clock::now().time_since_epoch());
}

void Game::StartGame(){
    isGameRunning = true;

    food_vec = {};
    food_vec.push_back(new Food(0, 0, &food_t, window));
    food_vec.push_back(new Food(0, 0, &food_t, window));
    food_vec[0]->Spawn();
    food_vec[1]->Spawn();

    head = new Head(300, 300, &head_t, window, difficulty);

    body_vec = {};
}

void Game::Stop(){
    isGameRunning = false;
    std::cout << "xd0";
    delete head;
    head = nullptr;
    std::cout << "xd1";
    for(auto p:food_vec){
        delete p;
    }
    std::cout << "xd2";
    for(auto p:body_vec){
        delete p;
    }
    std::cout << "xd3";
    food_vec.clear();
    std::cout << "xd4";
    body_vec.clear();
    std::cout << "xd5\n";
    //DEBUGGING BTW
}
