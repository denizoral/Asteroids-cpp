#include "Particle.hpp"
#include <random>

Particle::Particle(sf::Vector2f position, sf::Vector2f velocity, sf::Color color)
    : Entity(position, 1.0f)
    , m_color(color)
{
    m_type = EntityType::Particle;
    m_velocity = velocity;
    
    // Random number generation
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_real_distribution<float> lifetimeDist(PARTICLE_LIFETIME_MIN, PARTICLE_LIFETIME_MAX);
    
    m_maxLifetime = lifetimeDist(gen);
    m_lifetime = m_maxLifetime;
    
    m_shape.setSize(sf::Vector2f(2.0f, 2.0f));
    m_shape.setFillColor(m_color);
    m_shape.setOrigin(sf::Vector2f(1.0f, 1.0f));
}

void Particle::update(float deltaTime)
{
    move(deltaTime);
    
    // Decrease lifetime
    m_lifetime -= deltaTime;
    
    // Set inactive when lifetime expires
    if (m_lifetime <= 0.0f) {
        setInactive();
        return;
    }
    
    // Fade out over lifetime
    float alpha = (m_lifetime / m_maxLifetime) * 255.0f;
    sf::Color color = m_color;
    color.a = static_cast<std::uint8_t>(alpha);
    m_shape.setFillColor(color);
}

void Particle::render(sf::RenderWindow& window)
{
    m_shape.setPosition(m_position);
    window.draw(m_shape);
}
