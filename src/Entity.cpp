#include "Entity.hpp"
#include <cmath>

Entity::Entity(sf::Vector2f position, float radius)
    : m_position(position)
    , m_velocity(0.0f, 0.0f)
    , m_rotation(0.0f)
    , m_radius(radius)
    , m_active(true)
    , m_type(EntityType::Particle) // Default type, should be overridden
{
}

bool Entity::isActive() const
{
    return m_active;
}

void Entity::setInactive()
{
    m_active = false;
}

sf::Vector2f Entity::getPosition() const
{
    return m_position;
}

float Entity::getRadius() const
{
    return m_radius;
}

EntityType Entity::getType() const
{
    return m_type;
}

void Entity::move(float deltaTime)
{
    m_position += m_velocity * deltaTime;
    wrapAroundScreen();
}

bool Entity::collidesWith(const Entity& other) const
{
    float distance = std::hypot(
        m_position.x - other.m_position.x,
        m_position.y - other.m_position.y
    );
    
    return distance < (m_radius + other.m_radius);
}

void Entity::wrapAroundScreen()
{
    if (m_position.x < 0) {
        m_position.x = WINDOW_WIDTH;
    } else if (m_position.x > WINDOW_WIDTH) {
        m_position.x = 0;
    }
    
    if (m_position.y < 0) {
        m_position.y = WINDOW_HEIGHT;
    } else if (m_position.y > WINDOW_HEIGHT) {
        m_position.y = 0;
    }
}
