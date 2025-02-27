#include "Collision.hpp"
#include "AudioManager.hpp"
#include <random>
#include <iostream>

void Collision::checkCollisions(
    Player& player,
    std::vector<std::unique_ptr<Bullet>>& bullets,
    std::vector<std::unique_ptr<Asteroid>>& asteroids,
    std::vector<std::unique_ptr<Particle>>& particles,
    int& score
) {
    // Check bullet-asteroid collisions
    for (auto& bullet : bullets) {
        if (!bullet->isActive()) continue;
        
        for (auto& asteroid : asteroids) {
            if (!asteroid->isActive()) continue;
            
            if (bullet->collidesWith(*asteroid)) {
                handleBulletAsteroidCollision(*bullet, *asteroid, asteroids, particles, score);
                break; // A bullet can only hit one asteroid
            }
        }
    }
    
    // Check player-asteroid collisions (only if player is not invulnerable)
    if (!player.isInvulnerable()) {
        for (auto& asteroid : asteroids) {
            if (!asteroid->isActive()) continue;
            
            if (player.collidesWith(*asteroid)) {
                handlePlayerAsteroidCollision(player, *asteroid, particles);
                break; // Only handle one collision per frame for player
            }
        }
    }
}

void Collision::handleBulletAsteroidCollision(
    Bullet& bullet,
    Asteroid& asteroid,
    std::vector<std::unique_ptr<Asteroid>>& asteroids,
    std::vector<std::unique_ptr<Particle>>& particles,
    int& score
) {
    // Deactivate the bullet
    bullet.setInactive();
    
    // Add score
    score += asteroid.getPoints();
    
    // Create smaller asteroids if not already the smallest size
    if (asteroid.getSize() != AsteroidSize::Small) {
        AsteroidSize newSize = (asteroid.getSize() == AsteroidSize::Large) 
            ? AsteroidSize::Medium 
            : AsteroidSize::Small;
        
        // Create two smaller asteroids
        for (int i = 0; i < 2; ++i) {
            // Random direction offset
            std::random_device rd;
            std::mt19937 gen(rd());
            std::uniform_real_distribution<float> angleDist(0.0f, 2.0f * 3.14159f);
            
            float angle = angleDist(gen);
            sf::Vector2f offset(std::cos(angle) * 10.0f, std::sin(angle) * 10.0f);
            
            asteroids.push_back(std::make_unique<Asteroid>(
                asteroid.getPosition() + offset, 
                newSize
            ));
        }
    }
    
    // Create explosion particles
    createExplosionParticles(asteroid.getPosition(), particles);
    
    // Play explosion sound depending on asteroid size
    if (asteroid.getSize() == AsteroidSize::Small){
        std::cout << "SMALL collision detected" << std::endl;
        AudioManager::getInstance().playSound("explosion_small.wav");
    }
    else if (asteroid.getSize() == AsteroidSize::Medium){
        std::cout << "MEDIUM collision detected" << std::endl;
        AudioManager::getInstance().playSound("explosion_medium.wav");
    }
    else {
        std::cout << "LARGE collision detected" << std::endl;
        AudioManager::getInstance().playSound("explosion_medium.wav");
    }
    
    // Deactivate the asteroid
    asteroid.setInactive();
}

void Collision::handlePlayerAsteroidCollision(
    Player& player,
    Asteroid& asteroid,
    std::vector<std::unique_ptr<Particle>>& particles
) {
    // Player is hit
    player.hit();
    player.decreaseLives();
    
    // Create explosion particles at player position
    createExplosionParticles(player.getPosition(), particles, sf::Color::Red);
    
    // Play explosion sound
    AudioManager::getInstance().playSound("explosion.wav");
    
    // Deactivate the asteroid that hit the player
    asteroid.setInactive();
    
    // Reset player position (with invulnerability)
    player.reset();
}


void Collision::createExplosionParticles(
    sf::Vector2f position,
    std::vector<std::unique_ptr<Particle>>& particles,
    sf::Color color,
    int count
) {
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_real_distribution<float> angleDist(0.0f, 2.0f * 3.14159f);
    std::uniform_real_distribution<float> speedDist(PARTICLE_SPEED_MIN, PARTICLE_SPEED_MAX);
    
    for (int i = 0; i < count; ++i) {
        float angle = angleDist(gen);
        float speed = speedDist(gen);
        
        sf::Vector2f velocity(std::cos(angle) * speed, std::sin(angle) * speed);
        
        particles.push_back(std::make_unique<Particle>(position, velocity, color));
    }
}
