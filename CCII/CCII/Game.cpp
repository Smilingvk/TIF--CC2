#include "Game.h"
#include <iostream>

// Constantes para velocidades y gravedad
constexpr float SPEED = 0.5f;
constexpr float GRAVITY = 0.01f;
constexpr float JUMP_FORCE = 1.8f;
constexpr float GROUND_HEIGHT = 850.f;

// Definiciones de rutas de textura para el fondo, suelo, Fireboy y Watergirl
#define BACKGROUND_TEXTURE_PATH "C:\\Visual studio\\CCII\\fondo.png"
#define GROUND_TEXTURE_PATH "C:\\Visual studio\\CCII\\bloque.png"
#define FIREBOY_TEXTURE_PATH "C:\\Visual studio\\CCII\\fireboy.png"
#define WATERGIRL_TEXTURE_PATH "C:\\Visual studio\\CCII\\watergirl.png"

// Constructor: inicializa la ventana y los jugadores (Fireboy y Watergirl)
Game::Game()
    : window(sf::VideoMode(1200u, 900u), "Fireboy and Watergirl"),
    fireboy("fireboy.png"), watergirl("watergirl.png") {

    // Cargar textura de fondo
    if (!backgroundTexture.loadFromFile(BACKGROUND_TEXTURE_PATH)) {
        std::cerr << "Error al cargar la textura de fondo desde " << BACKGROUND_TEXTURE_PATH << std::endl;
    }
    backgroundSprite.setTexture(backgroundTexture);

    // Cargar textura de suelo
    if (!groundTexture.loadFromFile(GROUND_TEXTURE_PATH)) {
        std::cerr << "Error al cargar la textura del suelo desde " << GROUND_TEXTURE_PATH << std::endl;
    }
    groundSprite.setTexture(groundTexture);

    // Posicionar a Fireboy y Watergirl en el suelo
    fireboy.setPosition(100.f, GROUND_HEIGHT - fireboy.getBounds().height);
    watergirl.setPosition(200.f, GROUND_HEIGHT - watergirl.getBounds().height);

    // Configurar plataformas
    sf::RectangleShape plataforma1(sf::Vector2f(300.f, 20.f));
    plataforma1.setFillColor(sf::Color::White);
    plataforma1.setTexture(&groundTexture);
    plataforma1.setPosition(150.f, 700.f);
    platforms.push_back(plataforma1);

    sf::RectangleShape plataforma2(sf::Vector2f(300.f, 20.f));
    plataforma2.setFillColor(sf::Color::White);
    plataforma2.setTexture(&groundTexture);
    plataforma2.setPosition(550.f, 500.f);
    platforms.push_back(plataforma2);

    sf::RectangleShape plataforma3(sf::Vector2f(300.f, 20.f));
    plataforma3.setFillColor(sf::Color::White);
    plataforma3.setTexture(&groundTexture);
    plataforma3.setPosition(900.f, 300.f);
    platforms.push_back(plataforma3);

    sf::RectangleShape plataforma4(sf::Vector2f(350.f, 20.f)); // Aumentando la longitud de la plataforma 4
    plataforma4.setFillColor(sf::Color::White);
    plataforma4.setTexture(&groundTexture);
    plataforma4.setPosition(50.f, 400.f); // Moviendo más a la izquierda
    platforms.push_back(plataforma4);

    // Configurar áreas de fuego y agua
    fireArea.setSize(sf::Vector2f(80.f, 15.f));
    fireArea.setFillColor(sf::Color::Red);
    fireArea.setPosition(500.f, GROUND_HEIGHT - 20.f);

    waterArea.setSize(sf::Vector2f(80.f, 15.f));
    waterArea.setFillColor(sf::Color::Blue);
    waterArea.setPosition(700.f, GROUND_HEIGHT - 20.f);

    // Configurar puertas de salida
    fireDoor.setSize(sf::Vector2f(50.f, 100.f));
    fireDoor.setFillColor(sf::Color::Red);
    fireDoor.setPosition(1100.f, 200.f);

    waterDoor.setSize(sf::Vector2f(50.f, 100.f));
    waterDoor.setFillColor(sf::Color::Blue);
    waterDoor.setPosition(80.f, 300.f); // Ajustando la posición más a la izquierda
}

// Bucle principal del juego
void Game::run() {
    while (window.isOpen()) {
        processEvents();
        update();
        render();
    }
}

// Procesa eventos de la ventana
void Game::processEvents() {
    sf::Event event;
    while (window.pollEvent(event)) {
        if (event.type == sf::Event::Closed) {
            window.close();
        }
    }

    // Controles de salto para Fireboy y Watergirl
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::W)) {
        fireboy.jump(JUMP_FORCE);
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up)) {
        watergirl.jump(JUMP_FORCE);
    }
}

// Actualiza la lógica del juego
void Game::update() {
    // Limitar el movimiento dentro de los límites de la ventana
    sf::FloatRect bounds(5.f, 5.f, static_cast<float>(window.getSize().x) - 10.f, static_cast<float>(window.getSize().y) - 10.f);

    // Movimiento horizontal y aplicación de gravedad para Fireboy y Watergirl
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::A) && fireboy.getBounds().left > bounds.left) {
        fireboy.move(-SPEED, 0.f);
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::D) && fireboy.getBounds().left + fireboy.getBounds().width < bounds.left + bounds.width) {
        fireboy.move(SPEED, 0.f);
    }

    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left) && watergirl.getBounds().left > bounds.left) {
        watergirl.move(-SPEED, 0.f);
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right) && watergirl.getBounds().left + watergirl.getBounds().width < bounds.left + bounds.width) {
        watergirl.move(SPEED, 0.f);
    }

    // Aplicar gravedad a Fireboy y Watergirl
    fireboy.applyGravity(GRAVITY, GROUND_HEIGHT);
    watergirl.applyGravity(GRAVITY, GROUND_HEIGHT);

    // Verificar colisiones entre los personajes y el entorno
    checkCollisions();
}

// Renderiza todos los elementos en la ventana
void Game::render() {
    window.clear(sf::Color::Black);

    // Dibujar el fondo en mosaico
    for (int x = 0; x < window.getSize().x; x += backgroundTexture.getSize().x) {
        for (int y = 0; y < window.getSize().y; y += backgroundTexture.getSize().y) {
            backgroundSprite.setPosition(x, y);
            window.draw(backgroundSprite);
        }
    }

    // Dibujar el suelo en mosaico
    for (int x = 0; x < window.getSize().x; x += groundTexture.getSize().x) {
        groundSprite.setPosition(x, GROUND_HEIGHT - groundTexture.getSize().y);
        window.draw(groundSprite);
    }

    // Dibujar las plataformas
    for (const auto& platform : platforms) {
        window.draw(platform);
    }

    // Dibujar áreas de fuego y agua, y puertas
    window.draw(fireArea);
    window.draw(waterArea);
    window.draw(fireDoor);
    window.draw(waterDoor);

    // Dibujar a Fireboy y Watergirl
    fireboy.draw(window);
    watergirl.draw(window);

    window.display();
}

// Reinicia la posición y velocidad de Fireboy y Watergirl
void Game::resetGame() {
    fireboy.setPosition(100.f, GROUND_HEIGHT - fireboy.getBounds().height);
    watergirl.setPosition(200.f, GROUND_HEIGHT - watergirl.getBounds().height);
    fireboy.resetVerticalSpeed();
    watergirl.resetVerticalSpeed();
}

// Verifica las colisiones entre los personajes y el entorno
void Game::checkCollisions() {
    // Colisiones entre Watergirl y el área de fuego
    if (watergirl.getBounds().intersects(fireArea.getGlobalBounds())) {
        resetGame();
    }

    // Colisiones entre Fireboy y el área de agua
    if (fireboy.getBounds().intersects(waterArea.getGlobalBounds())) {
        resetGame();
    }

    // Verificar si Fireboy y Watergirl han llegado a las puertas
    if (fireboy.getBounds().intersects(fireDoor.getGlobalBounds()) && watergirl.getBounds().intersects(waterDoor.getGlobalBounds())) {
        window.close();
    }

    // Verificar colisiones entre Fireboy/Watergirl y las plataformas
    for (const auto& platform : platforms) {
        // Colisiones con Fireboy
        if (fireboy.getBounds().intersects(platform.getGlobalBounds())) {
            // Verificar colisiones verticales
            if (fireboy.getVerticalSpeed() > 0 && fireboy.getBounds().top + fireboy.getBounds().height - fireboy.getVerticalSpeed() <= platform.getPosition().y) {
                fireboy.setPosition(fireboy.getBounds().left, platform.getPosition().y - fireboy.getBounds().height);
                fireboy.resetVerticalSpeed();
            }
            else if (fireboy.getVerticalSpeed() < 0 && fireboy.getBounds().top >= platform.getPosition().y + platform.getSize().y) {
                fireboy.setPosition(fireboy.getBounds().left, platform.getPosition().y + platform.getSize().y);
                fireboy.resetVerticalSpeed();
            }
            // Verificar colisiones horizontales
            if (fireboy.getBounds().left < platform.getPosition().x + platform.getSize().x && fireboy.getBounds().left + fireboy.getBounds().width > platform.getPosition().x) {
                if (fireboy.getBounds().top + fireboy.getBounds().height > platform.getPosition().y && fireboy.getBounds().top < platform.getPosition().y + platform.getSize().y) {
                    if (fireboy.getBounds().left < platform.getPosition().x) {
                        fireboy.setPosition(platform.getPosition().x - fireboy.getBounds().width, fireboy.getBounds().top);
                    }
                    else {
                        fireboy.setPosition(platform.getPosition().x + platform.getSize().x, fireboy.getBounds().top);
                    }
                }
            }
        }

        // Colisiones con Watergirl
        if (watergirl.getBounds().intersects(platform.getGlobalBounds())) {
            // Verificar colisiones verticales
            if (watergirl.getVerticalSpeed() > 0 && watergirl.getBounds().top + watergirl.getBounds().height - watergirl.getVerticalSpeed() <= platform.getPosition().y) {
                watergirl.setPosition(watergirl.getBounds().left, platform.getPosition().y - watergirl.getBounds().height);
                watergirl.resetVerticalSpeed();
            }
            else if (watergirl.getVerticalSpeed() < 0 && watergirl.getBounds().top >= platform.getPosition().y + platform.getSize().y) {
                watergirl.setPosition(watergirl.getBounds().left, platform.getPosition().y + platform.getSize().y);
                watergirl.resetVerticalSpeed();
            }
            // Verificar colisiones horizontales
            if (watergirl.getBounds().left < platform.getPosition().x + platform.getSize().x && watergirl.getBounds().left + watergirl.getBounds().width > platform.getPosition().x) {
                if (watergirl.getBounds().top + watergirl.getBounds().height > platform.getPosition().y && watergirl.getBounds().top < platform.getPosition().y + platform.getSize().y) {
                    if (watergirl.getBounds().left < platform.getPosition().x) {
                        watergirl.setPosition(platform.getPosition().x - watergirl.getBounds().width, watergirl.getBounds().top);
                    }
                    else {
                        watergirl.setPosition(platform.getPosition().x + platform.getSize().x, watergirl.getBounds().top);
                    }
                }
            }
        }
    }
}
