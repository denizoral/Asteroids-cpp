#pragma once

#include <SFML/Audio.hpp>
#include <unordered_map>
#include <string>
#include <vector>
#include <memory>

class AudioManager {
public:
    static AudioManager& getInstance();
    
    // Prevent copying or assignment
    AudioManager(const AudioManager&) = delete;
    AudioManager& operator=(const AudioManager&) = delete;
    
    // Play a sound effect
    void playSound(const std::string& name);
    
    // Initialize sound effects
    void initializeSounds();
    
    // Update sounds (clean up finished sounds)
    void update();

private:
    AudioManager();
    
    std::unordered_map<std::string, sf::SoundBuffer> m_soundBuffers;
    std::vector<std::unique_ptr<sf::Sound>> m_activeSounds;
    
    // Maximum number of simultaneous sounds
    static constexpr unsigned int MAX_SOUNDS = 16;
};
