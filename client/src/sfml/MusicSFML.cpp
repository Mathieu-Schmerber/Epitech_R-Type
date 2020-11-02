/*
** EPITECH PROJECT, 2020
** RType
** File description:
** Created by Cyprien
*/


#include "sfml/MusicSFML.hpp"

void MusicSFML::loadFromFile(const std::string filename)
{
    if (!_music.openFromFile(filename)) {
        std::cerr << "\033[33mMusic WARNING : Invalid load of music " << filename << "\033[0m" << std::endl;
    }
}

void MusicSFML::play()
{
    setVolume(_volume);
    _music.play();
}

void MusicSFML::pause()
{
    _music.pause();
}

void MusicSFML::stop()
{
    _music.stop();
}

void MusicSFML::setVolume(float volume)
{
    _music.setVolume(volume);
}
