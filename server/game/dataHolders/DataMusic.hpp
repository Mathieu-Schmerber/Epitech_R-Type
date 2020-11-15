//
// Created by mathi on 15/11/2020.
//

#ifndef RTYPE_DATAMUSIC_HPP
#define RTYPE_DATAMUSIC_HPP

#include "graphical/AMusic.hpp"

class DataMusic : public Engine::AMusic {
public:
    explicit DataMusic(const std::string &filename, bool loop=true) : Engine::AMusic() {
        _file = filename;
    }

    ~DataMusic() = default;

    void loadFromFile(const std::string &filename) final {this->_file = filename;}

    void play(int volume) final {}

    void pause() final {}

    void stop() final {}

    void setVolume(double volume) final {
        AMusic::setVolume(volume);
    }

    [[nodiscard]] bool isPlaying() const override {return false;}

    [[nodiscard]] bool isPaused() const override {return false;}

    [[nodiscard]] bool isStopped() const override {return false;}

    void setLoop(bool loop) final {}

    [[nodiscard]] bool isLooping() const override {return false;}

    void close() final {}
};


#endif //RTYPE_DATAMUSIC_HPP