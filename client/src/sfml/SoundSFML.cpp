/*
** EPITECH PROJECT, 2020
** RType
** File description:
** Created by Cyprien
*/


#include "sfml/SoundSFML.hpp"

void SoundSFML::loadFromFile(const std::string &filename)
{
    if (_buffer.loadFromFile(filename)) {
        _sound.setBuffer(_buffer);
    } else {
        std::cerr << "\033[33mSound WARNING : Invalid load of sound " << filename << "\033[0m" << std::endl;
    }
}

void SoundSFML::play(int volume)
{
    setVolume(_volume);
    _sound.play();
}

void SoundSFML::pause()
{
    _sound.pause();
}

void SoundSFML::stop()
{
    _sound.stop();
}

void SoundSFML::setVolume(double volume)
{
    ASound::setVolume(volume);
    _sound.setVolume(static_cast<float>(volume));
}
