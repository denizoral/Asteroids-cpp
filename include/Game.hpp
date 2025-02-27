#pragma once

#include <SFML/Graphics.hpp>
#include <vector>
#include <memory>
#include "Player.hpp"
#include "Asteroid.hpp"
#include "Bullet.hpp"
#include "Particle.hpp"
#include "UI.hpp"
#include "Constants.hpp"

class Game {
public:
    Game();
    
    // Initialize the game
    void init();
    
    // Run the game loop
    void run();

private:
    // Handle user input
    void handleInput();
    
    // Update game state
    void update(float deltaTime);
    
    // Render the game
    void render();
    
    // Initialize a new level
    void initLevel();
    
    // Create a new bullet
    void createBullet();
    
    // Clean up inactive entities
    void cleanupEntities();
    
    // Reset the game
    void resetGame();
    
    // Window and rendering
    sf::RenderWindow m_window;
    sf::Clock m_clock;
    float m_deltaTime;
    
    // Game state
    GameState m_gameState;
    int m_score;
    int m_level;
    float m_levelStartTimer;
    
    // Entities
    Player m_player;
    std::vector<std::unique_ptr<Asteroid>> m_asteroids;
    std::vector<std::unique_ptr<Bullet>> m_bullets;
    std::vector<std::unique_ptr<Particle>> m_particles;
    
    // UI
    UI m_ui;
    
    // Input control
    bool m_spacePressed;
    bool m_pPressed;
};
