#include "Asteroid.hpp"
#include <cmath>
#include <random>

Asteroid::Asteroid(sf::Vector2f position, AsteroidSize size)
    : Entity(position, 0.0f)
    , m_size(size)
{
    m_type = EntityType::Asteroid;
    
    // Set radius based on asteroid size
    switch (m_size) {
        case AsteroidSize::Large:
            m_radius = ASTEROID_LARGE_RADIUS;
            break;
        case AsteroidSize::Medium:
            m_radius = ASTEROID_MEDIUM_RADIUS;
            break;
        case AsteroidSize::Small:
            m_radius = ASTEROID_SMALL_RADIUS;
            break;
    }
    
    // Random number generation
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_real_distribution<float> speedDist(ASTEROID_SPEED_MIN, ASTEROID_SPEED_MAX);
    std::uniform_real_distribution<float> angleDist(0.0f, 2.0f * 3.14159f);
    std::uniform_real_distribution<float> rotSpeedDist(ASTEROID_ROTATION_SPEED_MIN, ASTEROID_ROTATION_SPEED_MAX);
    
    // Random direction and speed
    float angle = angleDist(gen);
    float speed = speedDist(gen);
    m_velocity = sf::Vector2f(std::cos(angle) * speed, std::sin(angle) * speed);
    
    // Random rotation speed (positive or negative)
    m_rotationSpeed = rotSpeedDist(gen);
    if (gen() % 2 == 0) {
        m_rotationSpeed = -m_rotationSpeed;
    }
    
    generateShape();
}

void Asteroid::update(float deltaTime)
{
    move(deltaTime);
    
    // Rotate the asteroid
    m_rotation += m_rotationSpeed * deltaTime;
    
    // Keep rotation in [0, 360) range
    while (m_rotation < 0.0f) {
        m_rotation += 360.0f;
    }
    while (m_rotation >= 360.0f) {
        m_rotation -= 360.0f;
    }
}

void Asteroid::render(sf::RenderWindow& window)
{
    m_shape.setPosition(m_position);
    // Convert m_rotation (a float in degrees) into an sf::Angle using sf::degrees()
    m_shape.setRotation(sf::degrees(m_rotation));
    window.draw(m_shape);
}

AsteroidSize Asteroid::getSize() const
{
    return m_size;
}

int Asteroid::getPoints() const
{
    switch (m_size) {
        case AsteroidSize::Large:
            return ASTEROID_POINTS_LARGE;
        case AsteroidSize::Medium:
            return ASTEROID_POINTS_MEDIUM;
        case AsteroidSize::Small:
            return ASTEROID_POINTS_SMALL;
        default:
            return 0;
    }
}

void Asteroid::generateShape()
{
    // Random number generation
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<int> verticesDist(ASTEROID_VERTICES_MIN, ASTEROID_VERTICES_MAX);
    std::uniform_real_distribution<float> radiusVariationDist(0.5f, 1.5f);
    
    // Decide number of vertices
    int numVertices = verticesDist(gen);
    m_shape.setPointCount(numVertices);
    
    // Generate irregular polygon with random radius variations
    for (int i = 0; i < numVertices; ++i) {
        float angle = i * 2.0f * 3.14159f / numVertices;
        float radiusVariation = radiusVariationDist(gen);
        float vertexRadius = m_radius * radiusVariation;
        
        float x = std::cos(angle) * vertexRadius;
        float y = std::sin(angle) * vertexRadius;
        
        m_shape.setPoint(i, sf::Vector2f(x, y));
    }
    
    m_shape.setFillColor(sf::Color::Transparent);
    m_shape.setOutlineColor(sf::Color::White);
    m_shape.setOutlineThickness(1.0f);
    // Use a single sf::Vector2f as the origin
    m_shape.setOrigin(sf::Vector2f(0.0f, 0.0f));
}

Asteroid Asteroid::createRandom(const sf::Vector2f& playerPosition)
{
    std::random_device rd;
    std::mt19937 gen(rd());
    
    // Random position along the edge of the screen
    std::uniform_int_distribution<int> edgeDist(0, 3); // 0: top, 1: right, 2: bottom, 3: left
    std::uniform_real_distribution<float> positionDist;
    
    sf::Vector2f position;
    int edge = edgeDist(gen);
    
    switch (edge) {
        case 0: // Top edge
            positionDist = std::uniform_real_distribution<float>(0.0f, static_cast<float>(WINDOW_WIDTH));
            position = sf::Vector2f(positionDist(gen), 0.0f);
            break;
        case 1: // Right edge
            positionDist = std::uniform_real_distribution<float>(0.0f, static_cast<float>(WINDOW_HEIGHT));
            position = sf::Vector2f(static_cast<float>(WINDOW_WIDTH), positionDist(gen));
            break;
        case 2: // Bottom edge
            positionDist = std::uniform_real_distribution<float>(0.0f, static_cast<float>(WINDOW_WIDTH));
            position = sf::Vector2f(positionDist(gen), static_cast<float>(WINDOW_HEIGHT));
            break;
        case 3: // Left edge
            positionDist = std::uniform_real_distribution<float>(0.0f, static_cast<float>(WINDOW_HEIGHT));
            position = sf::Vector2f(0.0f, positionDist(gen));
            break;
    }
    
    // Ensure asteroid is not too close to player
    float minDistanceFromPlayer = 150.0f;
    float distanceToPlayer = std::hypot(
        position.x - playerPosition.x,
        position.y - playerPosition.y
    );
    
    if (distanceToPlayer < minDistanceFromPlayer) {
        // If too close, move it in the opposite direction from player
        sf::Vector2f direction = position - playerPosition;
        float length = std::hypot(direction.x, direction.y);
        direction /= length;
        position = playerPosition + direction * minDistanceFromPlayer;
    }
    
    // Create a large asteroid
    return Asteroid(position, AsteroidSize::Large);
}
