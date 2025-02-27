#include "Player.hpp"
#include "AudioManager.hpp"
#include "ResourceManager.hpp"
#include <cmath>
#include <iostream>

Player::Player()
    : Entity(sf::Vector2f(WINDOW_WIDTH / 2.0f, WINDOW_HEIGHT / 2.0f), 15.0f)
    , m_fireCooldown(0.0f)
    , m_lives(3)
    , m_invulnerable(false)
    , m_invulnerabilityTimer(0.0f)
    , m_blinkTimer(0.0f)
    , m_thrusting(false)
    // Initialize m_thrustSound with the thrust sound buffer from ResourceManager
    , m_thrustSound(ResourceManager::getInstance().getSoundBuffer("thrust.wav"))
{
    m_type = EntityType::Player;
    createShipShape();
    
    // Set the thrust sound to loop continuously
    m_thrustSound.setLooping(true);
}

void Player::createShipShape()
{
    m_shipShape.setPointCount(3);
    m_shipShape.setPoint(0, sf::Vector2f(20.0f, 0.0f));           // Nose
    m_shipShape.setPoint(1, sf::Vector2f(-10.0f, -10.0f));        // Left wing
    m_shipShape.setPoint(2, sf::Vector2f(-10.0f, 10.0f));         // Right wing
    
    m_shipShape.setFillColor(sf::Color::Transparent);
    m_shipShape.setOutlineColor(sf::Color::White);
    m_shipShape.setOutlineThickness(1.0f);
    m_shipShape.setOrigin(sf::Vector2f(0.0f, 0.0f));
}

void Player::update(float deltaTime)
{
    handleInput(deltaTime);
    move(deltaTime);
    
    // Apply friction to gradually slow down
    m_velocity *= PLAYER_FRICTION;
    
    // Update fire cooldown
    updateFireCooldown(deltaTime);
    
    // Update invulnerability
    if (m_invulnerable) {
        m_invulnerabilityTimer -= deltaTime;
        m_blinkTimer -= deltaTime;
        
        if (m_blinkTimer <= 0.0f) {
            m_blinkTimer = 0.1f; // Blink every 0.1 seconds
        }
        
        if (m_invulnerabilityTimer <= 0.0f) {
            m_invulnerable = false;
        }
    }
}

void Player::render(sf::RenderWindow& window)
{
    // Don't render if blinking during invulnerability
    if (m_invulnerable && m_blinkTimer > 0.05f) {
        return;
    }
    
    // Update ship position and rotation
    m_shipShape.setPosition(m_position);
    m_shipShape.setRotation(sf::degrees(m_rotation));
    
    window.draw(m_shipShape);
    
    // Draw thrust flame when thrusting
    if (m_thrusting) {
        sf::ConvexShape flame;
        flame.setPointCount(3);
        flame.setPoint(0, sf::Vector2f(-10.0f, 0.0f));
        flame.setPoint(1, sf::Vector2f(-20.0f, -5.0f));
        flame.setPoint(2, sf::Vector2f(-20.0f, 5.0f));
        
        flame.setFillColor(sf::Color::Yellow);
        flame.setOutlineColor(sf::Color::Red);
        flame.setOutlineThickness(1.0f);
        
        flame.setPosition(m_position);
        flame.setRotation(sf::degrees(m_rotation));
        
        window.draw(flame);
    }
}

void Player::handleInput(float deltaTime)
{
    bool thrustKeyPressed = sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Up) ||
                            sf::Keyboard::isKeyPressed(sf::Keyboard::Key::W);
    
    // Handle rotation (unchanged)
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Left) ||
        sf::Keyboard::isKeyPressed(sf::Keyboard::Key::A)) {
        rotate(deltaTime, -1.0f);
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Right) ||
        sf::Keyboard::isKeyPressed(sf::Keyboard::Key::D)) {
        rotate(deltaTime, 1.0f);
    }
    
    // Handle thrust and sound
    if (thrustKeyPressed) {
        thrust(deltaTime);
        m_thrusting = true;
        // If sound is paused, resume it; if not playing at all, start it.
        if (m_thrustSound.getStatus() == sf::Sound::Status::Paused) {
            m_thrustSound.play();  // resumes from where it left off
        } else if (m_thrustSound.getStatus() != sf::Sound::Status::Playing) {
            m_thrustSound.play();
        }
    } else {
        m_thrusting = false;
        // Instead of stopping (which resets playback), pause the sound.
        if (m_thrustSound.getStatus() == sf::Sound::Status::Playing) {
            m_thrustSound.pause();
        }
    }
}


void Player::thrust(float deltaTime)
{
    // Calculate thrust direction based on ship's rotation
    float radians = m_rotation * 3.14159f / 180.0f;
    sf::Vector2f direction(std::cos(radians), std::sin(radians));
    
    // Apply acceleration in the direction the ship is facing
    m_velocity += direction * PLAYER_ACCELERATION;
    

    if (!m_thrustSoundPlaying) {
        m_thrustSound.play();
        m_thrustSoundPlaying = true;
    }
    
    // Limit maximum speed
    float speed = std::hypot(m_velocity.x, m_velocity.y);
    std::cout << speed << std::endl;
    if (speed > PLAYER_MAX_SPEED) {
        m_velocity = m_velocity / speed * PLAYER_MAX_SPEED;
    }
}

void Player::rotate(float deltaTime, float direction)
{
    m_rotation += PLAYER_ROTATION_SPEED * direction * deltaTime;
    
    // Keep rotation in [0, 360) range
    while (m_rotation < 0.0f) {
        m_rotation += 360.0f;
    }
    while (m_rotation >= 360.0f) {
        m_rotation -= 360.0f;
    }
}

void Player::reset()
{
    m_position = sf::Vector2f(WINDOW_WIDTH / 2.0f, WINDOW_HEIGHT / 2.0f);
    m_velocity = sf::Vector2f(0.0f, 0.0f);
    m_rotation = -90.0f;  // Start facing upward
    m_active = true;
    m_invulnerable = true;
    m_invulnerabilityTimer = PLAYER_INVULNERABILITY_TIME;
}

bool Player::canFire() const
{
    return m_fireCooldown <= 0.0f;
}

void Player::setLives(int lives)
{
    m_lives = lives;
}

void Player::updateFireCooldown(float deltaTime)
{
    if (m_fireCooldown > 0.0f) {
        m_fireCooldown -= deltaTime;
    }
}

sf::Vector2f Player::getDirection() const
{
    float radians = m_rotation * 3.14159f / 180.0f;
    return sf::Vector2f(std::cos(radians), std::sin(radians));
}

int Player::getLives() const
{
    return m_lives;
}

void Player::decreaseLives()
{
    m_lives--;
}

void Player::hit()
{
    AudioManager::getInstance().playSound("explosion_small.wav");
    m_invulnerable = true;
    m_invulnerabilityTimer = PLAYER_INVULNERABILITY_TIME;
    m_blinkTimer = 0.1f;
}

bool Player::isInvulnerable() const
{
    return m_invulnerable;
}
