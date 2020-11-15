//
// Created by mathi on 15/11/2020.
//

#include "DataSound.hpp"

DataSound::DataSound(const std::string &filename) : Engine::ASound() {
    _file = filename;
    this->loadFromFile(filename);
}

void DataSound::loadFromFile(const std::string &filename) {}

void DataSound::play(int volume) {}

void DataSound::pause() {}

void DataSound::stop() {}

void DataSound::setVolume(double volume) {ASound::setVolume(volume);}

bool DataSound::isPlaying() const {return false;}
