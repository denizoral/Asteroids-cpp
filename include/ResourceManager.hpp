#pragma once

#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <unordered_map>
#include <string>
#include <memory>

class ResourceManager {
public:
    static ResourceManager& getInstance();
    
    // Prevent copying or assignment
    ResourceManager(const ResourceManager&) = delete;
    ResourceManager& operator=(const ResourceManager&) = delete;
    
    // Font handling
    sf::Font& getFont(const std::string& filename);
    
    // Sound handling
    sf::SoundBuffer& getSoundBuffer(const std::string& filename);
    
    // Initialize resources
    void loadResources();
    
private:
    ResourceManager() = default;
    
    std::unordered_map<std::string, sf::Font> m_fonts;
    std::unordered_map<std::string, sf::SoundBuffer> m_soundBuffers;
};
