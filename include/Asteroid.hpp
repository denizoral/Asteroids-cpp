#pragma once

#include "Entity.hpp"
#include <vector>
#include <random>

class Asteroid : public Entity {
public:
    Asteroid(sf::Vector2f position, AsteroidSize size);
    
    void update(float deltaTime) override;
    void render(sf::RenderWindow& window) override;
    
    // Get the size of the asteroid
    AsteroidSize getSize() const;
    
    // Get points value for destroying this asteroid
    int getPoints() const;
    
    // Create a random asteroid away from the player
    static Asteroid createRandom(const sf::Vector2f& playerPosition);

private:
    // Generate a random polygon shape for the asteroid
    void generateShape();
    
    sf::ConvexShape m_shape;
    AsteroidSize m_size;
    float m_rotationSpeed;
};
