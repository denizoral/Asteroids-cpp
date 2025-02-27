#pragma once

#include "Entity.hpp"

class Particle : public Entity {
public:
    Particle(sf::Vector2f position, sf::Vector2f velocity, sf::Color color);
    
    void update(float deltaTime) override;
    void render(sf::RenderWindow& window) override;

private:
    float m_lifetime;
    float m_maxLifetime;
    sf::Color m_color;
    sf::RectangleShape m_shape;
};
