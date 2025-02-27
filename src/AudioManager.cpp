#include "AudioManager.hpp"
#include "ResourceManager.hpp"
#include <iostream>
#include <algorithm>

AudioManager& AudioManager::getInstance()
{
    static AudioManager instance;
    return instance;
}

AudioManager::AudioManager()
{
    // Reserve space for active sounds
    m_activeSounds.reserve(MAX_SOUNDS);
}

void AudioManager::playSound(const std::string& name)
{
    // Get the sound buffer
    sf::SoundBuffer& buffer = ResourceManager::getInstance().getSoundBuffer(name);
    
    // Clean up finished sounds
    update();
    
    // If we've reached the maximum number of sounds, return
    if (m_activeSounds.size() >= MAX_SOUNDS) {
        return;
    }
    
    // Create and play the sound using the new constructor that accepts a buffer
    auto sound = std::make_unique<sf::Sound>(buffer);
    sound->play();
    
    // Add to active sounds
    m_activeSounds.push_back(std::move(sound));
}

void AudioManager::initializeSounds()
{
    // Ensure ResourceManager has loaded the sound resources
    ResourceManager::getInstance().loadResources();
}

void AudioManager::update()
{
    // Remove finished sounds
    m_activeSounds.erase(
        std::remove_if(
            m_activeSounds.begin(),
            m_activeSounds.end(),
            [](const std::unique_ptr<sf::Sound>& sound) {
                return sound->getStatus() == sf::Sound::Status::Stopped;
            }
        ),
        m_activeSounds.end()
    );
}
