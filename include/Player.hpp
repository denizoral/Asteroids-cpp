#pragma once

#include "Entity.hpp"
#include <vector>
#include <SFML/Audio.hpp>

class Player : public Entity {
public:
    Player();
    
    void update(float deltaTime) override;
    void render(sf::RenderWindow& window) override;
    
    // Handle input for player movement and actions
    void handleInput(float deltaTime);

    void setLives(int lives);
    
    // Reset the player when starting a new game or after death
    void reset();
    
    // Apply thrust to the player ship
    void thrust(float deltaTime);
    
    // Rotate the player ship
    void rotate(float deltaTime, float direction);
    
    // Check if player can fire (cooldown expired)
    bool canFire() const;
    
    // Update fire cooldown
    void updateFireCooldown(float deltaTime);
    
    // Get the direction the player is facing (for bullets)
    sf::Vector2f getDirection() const;
    
    // Get player's current lives
    int getLives() const;
    
    // Decrease player lives
    void decreaseLives();
    
    // Player hit by asteroid, become temporarily invulnerable
    void hit();
    
    // Check if player is currently invulnerable
    bool isInvulnerable() const;

private:
    // Create the ship shape
    void createShipShape();
    
    sf::ConvexShape m_shipShape;
    sf::Sound m_thrustSound;
    bool m_thrustSoundPlaying = false;
    float m_fireCooldown;
    int m_lives;
    bool m_invulnerable;
    float m_invulnerabilityTimer;
    float m_blinkTimer;  // For blinking effect when invulnerable
    bool m_thrusting;    // Is the player currently thrusting

};
