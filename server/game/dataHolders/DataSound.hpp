//
// Created by mathi on 15/11/2020.
//

#ifndef RTYPE_DATASOUND_HPP
#define RTYPE_DATASOUND_HPP

#include "graphical/ASound.hpp"

class DataSound : public Engine::ASound {
private:
    std::string file;

public:
    explicit DataSound(const std::string &filename);
    void loadFromFile(const std::string &filename) final;
    void play(int volume) final;
    void pause() final;
    void stop() final;
    void setVolume(double volume) final;
    [[nodiscard]] bool isPlaying() const final;
};


#endif //RTYPE_DATASOUND_HPP
