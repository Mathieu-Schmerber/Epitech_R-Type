/*
** EPITECH PROJECT, 2020
** RType
** File description:
** Created by Cyprien
*/

#include "sfml/MusicSFML.hpp"

void MusicSFML::loadFromFile(const std::string &filename)
{
    if (!_music->openFromFile(filename)) {
        std::cerr << "\033[33mMusic WARNING : Invalid load of music " << filename << "\033[0m" << std::endl;
    }
}

void MusicSFML::play(int volume)
{
    setVolume(volume);
    _music->play();
}

void MusicSFML::pause()
{
    _music->pause();
}

void MusicSFML::stop()
{
    _music->stop();
}

void MusicSFML::setVolume(double volume)
{
    AMusic::setVolume(volume);
    _volume = volume;
    _music->setVolume(static_cast<float>(volume));
}

void MusicSFML::setLoop(bool loop)
{
    _music->setLoop(loop);
}

bool MusicSFML::isPaused() const
{
    return _music->getStatus() == sf::SoundSource::Paused;
}

bool MusicSFML::isStopped() const
{
    return _music->getStatus() == sf::SoundSource::Stopped;
}

bool MusicSFML::isPlaying() const
{
    return _music->getStatus() == sf::SoundSource::Playing;
}

bool MusicSFML::isLooping() const
{
    return _music->getLoop();
}
