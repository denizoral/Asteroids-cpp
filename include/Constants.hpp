#pragma once

// Window settings
constexpr int WINDOW_WIDTH = 1024;
constexpr int WINDOW_HEIGHT = 768;
constexpr const char* WINDOW_TITLE = "Asteroids";

// Game settings
constexpr float PLAYER_SPEED = 300.0f;
constexpr float PLAYER_ROTATION_SPEED = 270.0f;
constexpr float PLAYER_FRICTION = 0.98f;
constexpr float PLAYER_ACCELERATION = 10.0f;
constexpr float PLAYER_MAX_SPEED = 500.0f;
constexpr float PLAYER_INVULNERABILITY_TIME = 3.0f;

// Bullet settings
constexpr float BULLET_SPEED = 600.0f;
constexpr float BULLET_LIFETIME = 3.0f;
constexpr float FIRE_COOLDOWN = 0.25f;

// Asteroid settings
constexpr float ASTEROID_SPEED_MIN = 50.0f;
constexpr float ASTEROID_SPEED_MAX = 150.0f;
constexpr float ASTEROID_ROTATION_SPEED_MIN = 20.0f;
constexpr float ASTEROID_ROTATION_SPEED_MAX = 70.0f;
constexpr int ASTEROID_VERTICES_MIN = 8;
constexpr int ASTEROID_VERTICES_MAX = 12;
constexpr float ASTEROID_LARGE_RADIUS = 40.0f;
constexpr float ASTEROID_MEDIUM_RADIUS = 20.0f;
constexpr float ASTEROID_SMALL_RADIUS = 10.0f;
constexpr int ASTEROID_POINTS_LARGE = 20;
constexpr int ASTEROID_POINTS_MEDIUM = 50;
constexpr int ASTEROID_POINTS_SMALL = 100;

// Particle settings
constexpr float PARTICLE_LIFETIME_MIN = 0.5f;
constexpr float PARTICLE_LIFETIME_MAX = 1.0f;
constexpr float PARTICLE_SPEED_MIN = 50.0f;
constexpr float PARTICLE_SPEED_MAX = 150.0f;
constexpr int PARTICLES_ON_DESTROY = 15;

// Game states
enum class GameState {
    MainMenu,
    Playing,
    GameOver,
    Paused
};

// Entity types
enum class EntityType {
    Player,
    Asteroid,
    Bullet,
    Particle
};

// Asteroid sizes
enum class AsteroidSize {
    Large,
    Medium,
    Small
};
