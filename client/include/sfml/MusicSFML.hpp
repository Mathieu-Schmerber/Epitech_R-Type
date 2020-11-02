/*
** EPITECH PROJECT, 2020
** RType
** File description:
** Created by Cyprien
*/


#ifndef RTYPE_MUSICSFML_HPP
#define RTYPE_MUSICSFML_HPP

#include <graphical/AMusic.hpp>
#include <SFML/Audio.hpp>

class MusicSFML : public Engine::AMusic {
public:
    MusicSFML() = default;

    void loadFromFile(const std::string filename) override;
    void play() override;
    void pause() override;
    void stop() override;
    void setVolume(float volume) override;

private:
    sf::Music _music;
};


#endif //RTYPE_MUSICSFML_HPP
