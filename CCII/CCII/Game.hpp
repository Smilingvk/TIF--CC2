#pragma once
#include <SFML/Graphics.hpp>
#include "Player.hpp"

class Game {
public:
    Game();
    void run();

private:
    void processEvents();
    void update(float deltaTime);
    void render();

    sf::RenderWindow window;
    Player player1;
    Player player2;
};
