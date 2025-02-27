#include "UI.hpp"
#include "ResourceManager.hpp"
#include <string>
#include <iostream>

UI::UI()
    : m_fontLoaded(false)
{
    // Try to load font
    try {
        m_font = ResourceManager::getInstance().getFont("arial.ttf");
        m_fontLoaded = true;
    } catch (const std::exception& e) {
        std::cerr << "Failed to load font: " << e.what() << std::endl;
    }
}

void UI::renderScore(sf::RenderWindow& window, int score)
{
    if (!m_fontLoaded) return;
    
    sf::Text scoreText(m_font, "Score: " + std::to_string(score), 24);
    scoreText.setFillColor(sf::Color::White);
    scoreText.setPosition(sf::Vector2f(20.f, 20.f));
    
    window.draw(scoreText);
}

void UI::renderVelocity(sf::RenderWindow& window, int deltaTime)
{
    if (!m_fontLoaded) return;
    
    sf::Text velocityText(m_font, "Velocity: " + std::to_string(deltaTime), 24);
    velocityText.setFillColor(sf::Color::White);
    velocityText.setPosition(sf::Vector2f(20.f, 90.f));
    
    window.draw(velocityText);
}

void UI::renderLives(sf::RenderWindow& window, int lives)
{
    if (!m_fontLoaded) return;
    
    sf::Text livesText(m_font, "Lives: " + std::to_string(lives), 24);
    livesText.setFillColor(sf::Color::White);
    livesText.setPosition(sf::Vector2f(20.f, 50.f));
    
    window.draw(livesText);
    
    // Draw ship icons for lives
    for (int i = 0; i < lives; ++i) {
        sf::ConvexShape ship;
        ship.setPointCount(3);
        ship.setPoint(0, sf::Vector2f(10.f, 0.f));
        ship.setPoint(1, sf::Vector2f(-5.f, -5.f));
        ship.setPoint(2, sf::Vector2f(-5.f, 5.f));
        
        ship.setFillColor(sf::Color::White);
        ship.setPosition(sf::Vector2f(110.f + i * 25.f, 60.f));
        ship.setRotation(sf::degrees(-90.f));
        
        window.draw(ship);
    }
}

void UI::renderLevel(sf::RenderWindow& window, int level)
{
    if (!m_fontLoaded) return;
    
    sf::Text levelText(m_font, "Level: " + std::to_string(level), 24);
    levelText.setFillColor(sf::Color::White);
    levelText.setPosition(sf::Vector2f(WINDOW_WIDTH - 150.f, 20.f));
    
    window.draw(levelText);
}

void UI::renderGameOver(sf::RenderWindow& window, int score)
{
    if (!m_fontLoaded) return;
    
    // Semi-transparent background
    sf::RectangleShape overlay;
    overlay.setSize(sf::Vector2f(WINDOW_WIDTH, WINDOW_HEIGHT));
    overlay.setFillColor(sf::Color(0, 0, 0, 200));
    window.draw(overlay);
    
    // Game Over text
    sf::Text gameOverText(m_font, "GAME OVER", 64);
    gameOverText.setFillColor(sf::Color::Red);
    {
        sf::FloatRect textRect = gameOverText.getLocalBounds();
        gameOverText.setOrigin(sf::Vector2f(textRect.position.x + textRect.size.x / 2.f,
                                             textRect.position.y + textRect.size.y / 2.f));
    }
    gameOverText.setPosition(sf::Vector2f(WINDOW_WIDTH / 2.f, WINDOW_HEIGHT / 2.f - 60.f));
    window.draw(gameOverText);
    
    // Final score text
    sf::Text finalScoreText(m_font, "Final Score: " + std::to_string(score), 32);
    finalScoreText.setFillColor(sf::Color::White);
    {
        sf::FloatRect textRect = finalScoreText.getLocalBounds();
        finalScoreText.setOrigin(sf::Vector2f(textRect.position.x + textRect.size.x / 2.f,
                                               textRect.position.y + textRect.size.y / 2.f));
    }
    finalScoreText.setPosition(sf::Vector2f(WINDOW_WIDTH / 2.f, WINDOW_HEIGHT / 2.f));
    window.draw(finalScoreText);
    
    // Restart instructions
    sf::Text restartText(m_font, "Press SPACE to restart", 24);
    restartText.setFillColor(sf::Color::White);
    {
        sf::FloatRect textRect = restartText.getLocalBounds();
        restartText.setOrigin(sf::Vector2f(textRect.position.x + textRect.size.x / 2.f,
                                            textRect.position.y + textRect.size.y / 2.f));
    }
    restartText.setPosition(sf::Vector2f(WINDOW_WIDTH / 2.f, WINDOW_HEIGHT / 2.f + 60.f));
    window.draw(restartText);
}

void UI::renderMainMenu(sf::RenderWindow& window)
{
    if (!m_fontLoaded) return;
    
    // Title text
    sf::Text titleText(m_font, "ASTEROIDS", 72);
    titleText.setFillColor(sf::Color::White);
    {
        sf::FloatRect textRect = titleText.getLocalBounds();
        titleText.setOrigin(sf::Vector2f(textRect.position.x + textRect.size.x / 2.f,
                                         textRect.position.y + textRect.size.y / 2.f));
    }
    titleText.setPosition(sf::Vector2f(WINDOW_WIDTH / 2.f, WINDOW_HEIGHT / 3.f));
    window.draw(titleText);
    
    // Start instructions
    sf::Text startText(m_font, "Press SPACE to start", 32);
    startText.setFillColor(sf::Color::White);
    {
        sf::FloatRect textRect = startText.getLocalBounds();
        startText.setOrigin(sf::Vector2f(textRect.position.x + textRect.size.x / 2.f,
                                         textRect.position.y + textRect.size.y / 2.f));
    }
    startText.setPosition(sf::Vector2f(WINDOW_WIDTH / 2.f, WINDOW_HEIGHT / 2.f + 60.f));
    window.draw(startText);
    
    // Controls instructions
    sf::Text controlsText(m_font, "Controls:\nArrow Keys/WASD - Move\nSpace - Fire\nP - Pause", 24);
    controlsText.setFillColor(sf::Color::White);
    {
        sf::FloatRect textRect = controlsText.getLocalBounds();
        controlsText.setOrigin(sf::Vector2f(textRect.position.x + textRect.size.x / 2.f,
                                            textRect.position.y + textRect.size.y / 2.f));
    }
    controlsText.setPosition(sf::Vector2f(WINDOW_WIDTH / 2.f, WINDOW_HEIGHT / 2.f + 150.f));
    window.draw(controlsText);
}

void UI::renderPauseMenu(sf::RenderWindow& window)
{
    if (!m_fontLoaded) return;
    
    // Semi-transparent background
    sf::RectangleShape overlay;
    overlay.setSize(sf::Vector2f(WINDOW_WIDTH, WINDOW_HEIGHT));
    overlay.setFillColor(sf::Color(0, 0, 0, 150));
    window.draw(overlay);
    
    // Pause text
    sf::Text pauseText(m_font, "PAUSED", 64);
    pauseText.setFillColor(sf::Color::White);
    {
        sf::FloatRect textRect = pauseText.getLocalBounds();
        pauseText.setOrigin(sf::Vector2f(textRect.position.x + textRect.size.x / 2.f,
                                         textRect.position.y + textRect.size.y / 2.f));
    }
    pauseText.setPosition(sf::Vector2f(WINDOW_WIDTH / 2.f, WINDOW_HEIGHT / 2.f - 50.f));
    window.draw(pauseText);
    
    // Resume instructions
    sf::Text resumeText(m_font, "Press P to resume", 32);
    resumeText.setFillColor(sf::Color::White);
    {
        sf::FloatRect textRect = resumeText.getLocalBounds();
        resumeText.setOrigin(sf::Vector2f(textRect.position.x + textRect.size.x / 2.f,
                                          textRect.position.y + textRect.size.y / 2.f));
    }
    resumeText.setPosition(sf::Vector2f(WINDOW_WIDTH / 2.f, WINDOW_HEIGHT / 2.f + 50.f));
    window.draw(resumeText);
}
