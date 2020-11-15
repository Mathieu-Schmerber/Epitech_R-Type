/*
** EPITECH PROJECT, 2020
** RType
** File description:
** Created by Cyprien
*/


#ifndef RTYPE_SOUNDSFML_HPP
#define RTYPE_SOUNDSFML_HPP

#include <graphical/ASound.hpp>
#include <SFML/Audio.hpp>
#include <iostream>

class SoundSFML : public Engine::ASound {
public:
    SoundSFML() = default;

    void loadFromFile(const std::string &filename) final;
    void play(int volume) final;
    void pause() final;
    void stop() final;
    void setVolume(double volume) final;

private:
    sf::SoundBuffer _buffer;
    sf::Sound _sound;
};


#endif //RTYPE_SOUNDSFML_HPP
