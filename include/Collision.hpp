#pragma once

#include "Entity.hpp"
#include "Player.hpp"
#include "Asteroid.hpp"
#include "Bullet.hpp"
#include "Particle.hpp"  // Added include for Particle
#include <vector>
#include <memory>

class Collision {
public:
    // Check for collisions between entities and handle them
    static void checkCollisions(
        Player& player,
        std::vector<std::unique_ptr<Bullet>>& bullets,
        std::vector<std::unique_ptr<Asteroid>>& asteroids,
        std::vector<std::unique_ptr<Particle>>& particles,
        int& score
    );

private:
    // Handle collision between bullet and asteroid
    static void handleBulletAsteroidCollision(
        Bullet& bullet,
        Asteroid& asteroid,
        std::vector<std::unique_ptr<Asteroid>>& asteroids,
        std::vector<std::unique_ptr<Particle>>& particles,
        int& score
    );
    
    // Handle collision between player and asteroid
    static void handlePlayerAsteroidCollision(
        Player& player,
        Asteroid& asteroid,
        std::vector<std::unique_ptr<Particle>>& particles
    );
    
    // Create explosion particles
    static void createExplosionParticles(
        sf::Vector2f position,
        std::vector<std::unique_ptr<Particle>>& particles,
        sf::Color color = sf::Color::White,
        int count = PARTICLES_ON_DESTROY
    );
};
