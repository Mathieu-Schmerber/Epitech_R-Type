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

    void loadFromFile(const std::string filename) final;
    void play() final;
    void pause() final;
    void stop() final;
    void setVolume(float volume) final;
    bool isPlaying() const;
    bool isPaused() const;
    bool isStopped() const;
    void setLoop(bool loop=true);
    bool isLooping() const;

private:
    sf::Music _music;
};


#endif //RTYPE_MUSICSFML_HPP
