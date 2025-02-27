#include "ResourceManager.hpp"
#include <iostream>
#include <filesystem>

ResourceManager& ResourceManager::getInstance()
{
    static ResourceManager instance;
    return instance;
}

sf::Font& ResourceManager::getFont(const std::string& filename)
{
    // Check if font is already loaded
    auto it = m_fonts.find(filename);
    if (it != m_fonts.end()) {
        return it->second;
    }
    
    // Load the font
    sf::Font font;
    std::string path = "resources/fonts/" + filename;
    
    if (!font.openFromFile(path)) {
        std::cerr << "Failed to load font: " << path << std::endl;
        
        // Try to find the file in the current directory
        std::string currentDir = std::filesystem::current_path().string();
        std::cerr << "Current directory: " << currentDir << std::endl;
        
        // Load a fallback font if available
        if (m_fonts.size() > 0) {
            return m_fonts.begin()->second;
        }
        
        // If no fallback, just return whatever we have
        m_fonts[filename] = font;
        return m_fonts[filename];
    }
    
    // Store and return the font
    m_fonts[filename] = font;
    return m_fonts[filename];
}

sf::SoundBuffer& ResourceManager::getSoundBuffer(const std::string& filename)
{
    // Check if sound buffer is already loaded
    auto it = m_soundBuffers.find(filename);
    if (it != m_soundBuffers.end()) {
        return it->second;
    }
    
    // Load the sound buffer
    sf::SoundBuffer buffer;
    std::string path = "resources/sounds/" + filename;
    
    if (!buffer.loadFromFile(path)) {
        std::cerr << "Failed to load sound: " << path << std::endl;
        
        // If no sound found, just return an empty buffer
        m_soundBuffers[filename] = buffer;
        return m_soundBuffers[filename];
    }
    
    // Store and return the sound buffer
    m_soundBuffers[filename] = buffer;
    return m_soundBuffers[filename];
}

void ResourceManager::loadResources()
{
    // Preload fonts
    getFont("arial.ttf");
    
    // Preload sounds
    getSoundBuffer("fire.wav");
    getSoundBuffer("explosion_small.wav");
    getSoundBuffer("explosion_medium.wav");
    getSoundBuffer("explosion_large.wav");
    getSoundBuffer("thrust.wav");
}
