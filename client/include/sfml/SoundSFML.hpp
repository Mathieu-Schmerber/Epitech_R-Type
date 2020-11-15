/*!
 * @file SoundSFML.hpp
 * @brief Manage SFML's sounds
 * @authors Cyprien.R
 * @version 1.0
 * @date 14/11/2020
 *
*/


#ifndef RTYPE_SOUNDSFML_HPP
#define RTYPE_SOUNDSFML_HPP

#include <graphical/ASound.hpp>
#include <SFML/Audio.hpp>
#include <iostream>

class SoundSFML : public Engine::ASound {
public:
    /*!
     * \brief SoundSFML default constructor
     *
    */
    SoundSFML() = default;

    void loadFromFile(const std::string &filename) final;
    void play() final;
    void pause() final;
    void stop() final;
    void setVolume(double volume) final;

private:
    sf::SoundBuffer _buffer;
    sf::Sound _sound;
};


#endif //RTYPE_SOUNDSFML_HPP
