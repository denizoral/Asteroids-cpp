#pragma once

#include <SFML/Graphics.hpp>
#include "Constants.hpp"

class UI {
public:
    UI();
    
    // Render the score
    void renderScore(sf::RenderWindow& window, int score);
    
    // Render the lives
    void renderLives(sf::RenderWindow& window, int lives);
    
    // Render the level
    void renderLevel(sf::RenderWindow& window, int level);
    
    // Render game over screen
    void renderGameOver(sf::RenderWindow& window, int score);
    
    // Render main menu
    void renderMainMenu(sf::RenderWindow& window);
    
    // Render pause menu
    void renderPauseMenu(sf::RenderWindow& window);

    void renderVelocity(sf::RenderWindow& window, int deltaTime);

private:
    sf::Font m_font;
    bool m_fontLoaded;
};
