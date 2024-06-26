#include "Player.h"
#include <iostream>

// Definiciones de rutas de textura para Fireboy y Watergirl
#define FIREBOY_TEXTURE_PATH "C:\\Visual studio\\CCII\\fireboy.png"
#define WATERGIRL_TEXTURE_PATH "C:\\Visual studio\\CCII\\watergirl.png"

// Constructor: carga la textura del jugador según el archivo proporcionado
Player::Player(const std::string& textureFile) : verticalSpeed(0.f), onGround(false) {
    std::string fullPath;

    // Determina la ruta completa de la textura basado en el nombre del archivo
    if (textureFile == "fireboy.png") {
        fullPath = FIREBOY_TEXTURE_PATH;
    }
    else if (textureFile == "watergirl.png") {
        fullPath = WATERGIRL_TEXTURE_PATH;
    }
    else {
        // Manejo de error si se proporciona un nombre de archivo desconocido
        std::cerr << "Error: Nombre de archivo de textura desconocido " << textureFile << std::endl;
        return;
    }

    // Intenta cargar la textura desde la ruta completa
    std::cout << "Intentando cargar la textura desde: " << fullPath << std::endl;
    if (!texture.loadFromFile(fullPath)) {
        std::cerr << "Error al cargar la textura desde " << fullPath << std::endl;
    }
    else {
        std::cout << "Textura cargada exitosamente desde " << fullPath << std::endl;
    }

    // Configura el sprite del jugador con la textura cargada
    sprite.setTexture(texture);
}

// Establece la posición del jugador en la ventana
void Player::setPosition(float x, float y) {
    sprite.setPosition(x, y);
}

// Mueve al jugador según los desplazamientos dados
void Player::move(float offsetX, float offsetY) {
    sprite.move(offsetX, offsetY);
}

// Dibuja al jugador en la ventana proporcionada
void Player::draw(sf::RenderWindow& window) {
    window.draw(sprite);
}

// Devuelve los límites globales del jugador (para colisiones y posicionamiento)
sf::FloatRect Player::getBounds() const {
    return sprite.getGlobalBounds();
}

// Aplica la gravedad al jugador si no está en el suelo, limitándolo a una altura de suelo
void Player::applyGravity(float gravity, float groundHeight) {
    if (!onGround) {
        verticalSpeed += gravity;
        sprite.move(0.f, verticalSpeed);
    }

    // Ajusta la posición del jugador al suelo si ha tocado o superado la altura del suelo
    if (sprite.getPosition().y + sprite.getGlobalBounds().height >= groundHeight) {
        sprite.setPosition(sprite.getPosition().x, groundHeight - sprite.getGlobalBounds().height);
        verticalSpeed = 0.f;
        onGround = true;
    }
    else {
        onGround = false;
    }
}

// Hace saltar al jugador aplicándole una fuerza de salto si está en el suelo
void Player::jump(float jumpForce) {
    if (onGround) {
        verticalSpeed = -jumpForce;
        onGround = false;
    }
}

// Reinicia la velocidad vertical del jugador (útil al reiniciar o resetear)
void Player::resetVerticalSpeed() {
    verticalSpeed = 0.f;
}

// Verifica si el jugador está en el suelo
bool Player::isOnGround() const {
    return onGround;
}

// Establece el estado de "en el suelo" del jugador
void Player::setOnGround(bool onGround) {
    this->onGround = onGround;
}

// Devuelve la velocidad vertical actual del jugador
float Player::getVerticalSpeed() const {
    return verticalSpeed;
}
