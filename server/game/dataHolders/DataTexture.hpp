//
// Created by mathi on 07/11/2020.
//

#ifndef RTYPE_DATATEXTURE_HPP
#define RTYPE_DATATEXTURE_HPP

#include "graphical/ATexture.hpp"

class DataTexture : public Engine::ATexture {
public:
    explicit DataTexture(const std::string& filename) : Engine::ATexture(filename) {}
    void loadFromFile(std::string filename) final {}
};


#endif //RTYPE_DATATEXTURE_HPP
