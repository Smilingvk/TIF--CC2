#pragma once
#include <SFML/Graphics.hpp>

class Player {
public:
    Player(sf::Color color, float x, float y, sf::Keyboard::Key up, sf::Keyboard::Key down, sf::Keyboard::Key left, sf::Keyboard::Key right);
    void handleInput();
    void update(float deltaTime);
    void draw(sf::RenderWindow& window);

private:
    sf::RectangleShape shape;
    sf::Vector2f velocity;
    float speed;
    sf::Keyboard::Key upKey, downKey, leftKey, rightKey;
};
