/*!
 * @file MusicSFML.hpp
 * @brief Manage SFML's music
 * @authors Cyprien.R
 * @version 1.0
 * @date 14/11/2020
 *
*/


#ifndef RTYPE_MUSICSFML_HPP
#define RTYPE_MUSICSFML_HPP

#include <graphical/AMusic.hpp>
#include <SFML/Audio.hpp>

class MusicSFML : public Engine::AMusic {
public:
    /*!
     * \brief MusicSFML constructor
     * \param filename music filename
     * \param loop set if the music has to be played as loop
     *
    */
    explicit MusicSFML(const std::string &filename, bool loop=true) : Engine::AMusic() {
        loadFromFile(filename);
        setLoop(loop);
    }
    ~MusicSFML() {
        stop();
        delete _music;
    }

    void loadFromFile(const std::string &filename) final;
    void play() final;
    void pause() final;
    void stop() final;
    void setVolume(double volume) final;
    [[nodiscard]] bool isPlaying() const final;
    [[nodiscard]] bool isPaused() const final;
    [[nodiscard]] bool isStopped() const final;
    void setLoop(bool loop) final;
    [[nodiscard]] bool isLooping() const final;
    void close() final {
        stop();
        delete _music;
    }

private:
    sf::Music *_music = new sf::Music();
};


#endif //RTYPE_MUSICSFML_HPP
