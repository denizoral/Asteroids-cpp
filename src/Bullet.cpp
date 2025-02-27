#include "Bullet.hpp"
#include <cmath>

Bullet::Bullet(sf::Vector2f position, sf::Vector2f direction)
    : Entity(position, 2.0f)
    , m_lifetime(BULLET_LIFETIME)
{
    m_type = EntityType::Bullet;
    m_velocity = direction * BULLET_SPEED;
    
    m_shape.setRadius(m_radius);
    m_shape.setFillColor(sf::Color::White);
    m_shape.setOrigin(sf::Vector2f(m_radius, m_radius));
}

void Bullet::update(float deltaTime)
{
    move(deltaTime);
    
    // Decrease lifetime
    m_lifetime -= deltaTime;
    
    // Set inactive when lifetime expires
    if (m_lifetime <= 0.0f) {
        setInactive();
    }
}

void Bullet::render(sf::RenderWindow& window)
{
    m_shape.setPosition(m_position);
    window.draw(m_shape);
}
