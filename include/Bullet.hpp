#pragma once

#include "Entity.hpp"

class Bullet : public Entity {
public:
    Bullet(sf::Vector2f position, sf::Vector2f direction);
    
    void update(float deltaTime) override;
    void render(sf::RenderWindow& window) override;

private:
    float m_lifetime;
    sf::CircleShape m_shape;
};
