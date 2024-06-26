#ifndef GAME_H
#define GAME_H

#include <SFML/Graphics.hpp>
#include "Player.h"
#include <vector>

class Game {
public:
    Game(); // Constructor de la clase Game
    void run(); // Función principal para ejecutar el juego

private:
    void processEvents(); // Procesa los eventos de entrada
    void update(); // Actualiza la lógica del juego
    void render(); // Renderiza los elementos del juego
    void resetGame(); // Reinicia el juego
    void checkCollisions(); // Verifica las colisiones en el juego

    sf::RenderWindow window; // Ventana principal del juego
    Player fireboy; // Jugador Fireboy
    Player watergirl; // Jugador Watergirl
    std::vector<sf::RectangleShape> platforms; // Vector de plataformas
    sf::RectangleShape fireArea; // Área de fuego
    sf::RectangleShape waterArea; // Área de agua
    sf::RectangleShape fireDoor; // Puerta de Fireboy
    sf::RectangleShape waterDoor; // Puerta de Watergirl
    sf::Texture backgroundTexture; // Textura del fondo
    sf::Sprite backgroundSprite; // Sprite del fondo
    sf::Texture groundTexture; // Textura del suelo
    sf::Sprite groundSprite; // Sprite del suelo
};

#endif // GAME_H
