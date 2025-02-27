#pragma once

#include <SFML/Graphics.hpp>
#include "Constants.hpp"

class Entity {
public:
    Entity(sf::Vector2f position, float radius);
    virtual ~Entity() = default;

    virtual void update(float deltaTime) = 0;
    virtual void render(sf::RenderWindow& window) = 0;
    
    // Check if the entity is active
    bool isActive() const;
    
    // Set entity as inactive (to be removed)
    void setInactive();
    
    // Get the position of the entity
    sf::Vector2f getPosition() const;
    
    // Get the radius for collision detection
    float getRadius() const;
    
    // Get the type of entity
    EntityType getType() const;
    
    // Move the entity by the velocity
    void move(float deltaTime);
    
    // Check if this entity collides with another
    bool collidesWith(const Entity& other) const;
    
    // Wrap around screen edges
    void wrapAroundScreen();

protected:
    sf::Vector2f m_position;
    sf::Vector2f m_velocity;
    float m_rotation;
    float m_radius;
    bool m_active;
    EntityType m_type;
};
