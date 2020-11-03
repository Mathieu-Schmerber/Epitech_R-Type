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
    MusicSFML(const std::string filename, bool loop=true) : Engine::AMusic() {
        loadFromFile(filename);
        setLoop(loop);
        std::cout << "Oui, il va y avoir des devices not closed, c'est en cours de fix" << std::endl;
    }
    ~MusicSFML() {
        std::cout << "Prévenir Cyprien si ce print pop" << std::endl;
        stop(); // FIXME on ne passe pas ici, alors qu'on devrait. La classe est pas correctement détruite
    }

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
