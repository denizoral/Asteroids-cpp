#include "Game.hpp"
#include "ResourceManager.hpp"
#include "AudioManager.hpp"
#include "Collision.hpp"
#include <iostream>
#include <variant>

Game::Game()
    : m_window(sf::VideoMode({WINDOW_WIDTH, WINDOW_HEIGHT}), WINDOW_TITLE)
    , m_deltaTime(0.0f)
    , m_gameState(GameState::MainMenu)
    , m_score(0)
    , m_level(1)
    , m_levelStartTimer(0.0f)
    , m_player()
    , m_ui()
    , m_spacePressed(false)
    , m_pPressed(false)
{
}

void Game::init()
{
    // Set up window
    m_window.setFramerateLimit(60);
    
    // Initialize resources
    ResourceManager::getInstance().loadResources();
    AudioManager::getInstance().initializeSounds();
    
    // Reset the player
    m_player.reset();
    
    // Clear entities
    m_asteroids.clear();
    m_bullets.clear();
    m_particles.clear();
    
    // Initialize first level
    initLevel();
}

void Game::run()
{
    init();
    
    // Game loop
    while (m_window.isOpen()) {
        // Calculate delta time
        m_deltaTime = m_clock.restart().asSeconds();
        
        // Cap delta time to avoid physics issues
        if (m_deltaTime > 0.1f) {
            m_deltaTime = 0.1f;
        }
        
        // Handle events
        while (auto event = m_window.pollEvent()) {
            if (event->is<sf::Event::Closed>()) {
                m_window.close();
            }
        }


        handleInput();
        update(m_deltaTime);
        render();
    }
}

void Game::handleInput()
{
    // Space key (fire bullet or start game)
    bool spacePressed = sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Space);
    
    if (spacePressed && !m_spacePressed) {
        if (m_gameState == GameState::Playing) {
            createBullet();
            AudioManager::getInstance().playSound("fire.wav");
        } else if (m_gameState == GameState::MainMenu || m_gameState == GameState::GameOver) {
            resetGame();
            m_gameState = GameState::Playing;
        }
    }
    
    m_spacePressed = spacePressed;
    
    // P key (pause/unpause)
    bool pPressed = sf::Keyboard::isKeyPressed(sf::Keyboard::Key::P);
    
    if (pPressed && !m_pPressed) {
        if (m_gameState == GameState::Playing) {
            m_gameState = GameState::Paused;
        } else if (m_gameState == GameState::Paused) {
            m_gameState = GameState::Playing;
        }
    }
    
    m_pPressed = pPressed;
}

void Game::update(float deltaTime)
{
    // Don't update if paused or in menu
    if (m_gameState != GameState::Playing) {
        return;
    }
    
    // Update level start timer
    if (m_levelStartTimer > 0.0f) {
        m_levelStartTimer -= deltaTime;
        return;
    }
    
    // Check if all asteroids are destroyed to start next level
    bool allAsteroidsDestroyed = true;
    for (const auto& asteroid : m_asteroids) {
        if (asteroid->isActive()) {
            allAsteroidsDestroyed = false;
            break;
        }
    }
    
    if (allAsteroidsDestroyed) {
        m_level++;
        initLevel();
        return;
    }
    
    // Update player
    m_player.update(deltaTime);
    
    // Update bullets
    for (auto& bullet : m_bullets) {
        if (bullet->isActive()) {
            bullet->update(deltaTime);
        }
    }
    
    // Update asteroids
    for (auto& asteroid : m_asteroids) {
        if (asteroid->isActive()) {
            asteroid->update(deltaTime);
        }
    }
    
    // Update particles
    for (auto& particle : m_particles) {
        if (particle->isActive()) {
            particle->update(deltaTime);
        }
    }
    
    // Check collisions
    Collision::checkCollisions(m_player, m_bullets, m_asteroids, m_particles, m_score);
    
    // Clean up inactive entities
    cleanupEntities();
    
    // Check for game over
    if (m_player.getLives() <= 0) {
        m_gameState = GameState::GameOver;
    }
    
    // Update audio manager to clean up finished sounds
    AudioManager::getInstance().update();
}

void Game::render()
{
    m_window.clear(sf::Color::Black);
    
    switch (m_gameState) {
        case GameState::MainMenu:
            m_ui.renderMainMenu(m_window);
            break;
            
        case GameState::Playing:
        case GameState::Paused:
            // Render asteroids
            for (const auto& asteroid : m_asteroids) {
                if (asteroid->isActive()) {
                    asteroid->render(m_window);
                }
            }
            
            // Render bullets
            for (const auto& bullet : m_bullets) {
                if (bullet->isActive()) {
                    bullet->render(m_window);
                }
            }
            
            // Render particles
            for (const auto& particle : m_particles) {
                if (particle->isActive()) {
                    particle->render(m_window);
                }
            }
            
            // Render player
            m_player.render(m_window);
            
            // Render UI
            m_ui.renderScore(m_window, m_score);
            m_ui.renderLives(m_window, m_player.getLives());
            m_ui.renderLevel(m_window, m_level);
            m_ui.renderVelocity(m_window, m_deltaTime);
            
            // Render pause menu if paused
            if (m_gameState == GameState::Paused) {
                m_ui.renderPauseMenu(m_window);
            }
            break;
            
        case GameState::GameOver:
            // Still render the game in the background
            for (const auto& asteroid : m_asteroids) {
                if (asteroid->isActive()) {
                    asteroid->render(m_window);
                }
            }
            
            for (const auto& bullet : m_bullets) {
                if (bullet->isActive()) {
                    bullet->render(m_window);
                }
            }
            
            for (const auto& particle : m_particles) {
                if (particle->isActive()) {
                    particle->render(m_window);
                }
            }
            
            m_ui.renderGameOver(m_window, m_score);
            break;
    }
    
    m_window.display();
}

void Game::initLevel()
{
    // Clear old asteroids
    m_asteroids.clear();
    
    // Number of asteroids based on level
    int numAsteroids = 4 + (m_level - 1) * 2;
    numAsteroids = std::min(numAsteroids, 12); // Cap at 12 asteroids
    
    // Create asteroids
    for (int i = 0; i < numAsteroids; ++i) {
        m_asteroids.push_back(std::make_unique<Asteroid>(
            Asteroid::createRandom(m_player.getPosition())
        ));
    }
    
    // Set up level start timer
    m_levelStartTimer = 2.0f;
}

void Game::createBullet()
{
    if (!m_player.canFire()) {
        return;
    }
    
    // Get player position and direction
    sf::Vector2f position = m_player.getPosition();
    sf::Vector2f direction = m_player.getDirection();
    
    // Offset the bullet position to start at the nose of the ship
    position += direction * 20.0f;
    
    // Create the bullet
    m_bullets.push_back(std::make_unique<Bullet>(position, direction));
    
    // Reset player's fire cooldown
    m_player.updateFireCooldown(FIRE_COOLDOWN);
}

void Game::cleanupEntities()
{
    // Remove inactive bullets
    m_bullets.erase(
        std::remove_if(
            m_bullets.begin(),
            m_bullets.end(),
            [](const std::unique_ptr<Bullet>& bullet) {
                return !bullet->isActive();
            }
        ),
        m_bullets.end()
    );
    
    // Remove inactive asteroids
    m_asteroids.erase(
        std::remove_if(
            m_asteroids.begin(),
            m_asteroids.end(),
            [](const std::unique_ptr<Asteroid>& asteroid) {
                return !asteroid->isActive();
            }
        ),
        m_asteroids.end()
    );
    
    // Remove inactive particles
    m_particles.erase(
        std::remove_if(
            m_particles.begin(),
            m_particles.end(),
            [](const std::unique_ptr<Particle>& particle) {
                return !particle->isActive();
            }
        ),
        m_particles.end()
    );
}

void Game::resetGame()
{
    m_score = 0;
    m_level = 1;
    m_player.reset();
    m_player.setLives(3);
    m_bullets.clear();
    m_asteroids.clear();
    m_particles.clear();
    
    initLevel();
}
