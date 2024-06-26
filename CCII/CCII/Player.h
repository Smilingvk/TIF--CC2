#ifndef PLAYER_H
#define PLAYER_H

#include <SFML/Graphics.hpp>

class Player {
public:
    Player(const std::string& textureFile); // Constructor que carga la textura del jugador
    void setPosition(float x, float y); // Establece la posición del jugador
    void move(float offsetX, float offsetY); // Mueve al jugador
    void draw(sf::RenderWindow& window); // Dibuja al jugador en la ventana
    void applyGravity(float gravity, float groundHeight); // Aplica gravedad al jugador
    void jump(float jumpForce); // Hace saltar al jugador
    sf::FloatRect getBounds() const; // Devuelve los límites del jugador
    void resetVerticalSpeed(); // Reinicia la velocidad vertical del jugador
    bool isOnGround() const; // Verifica si el jugador está en el suelo
    float getVerticalSpeed() const; // Devuelve la velocidad vertical del jugador

    // Función para establecer si el jugador está en el suelo
    void setOnGround(bool onGround);

private:
    sf::Texture texture; // Textura del jugador
    sf::Sprite sprite; // Sprite del jugador
    float verticalSpeed; // Velocidad vertical del jugador
    bool onGround; // Indicador si el jugador está en el suelo
};

#endif // PLAYER_H
