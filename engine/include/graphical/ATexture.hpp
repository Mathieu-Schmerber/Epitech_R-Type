/*
** EPITECH PROJECT, 2020
** RType
** File description:
** Created by Cyprien
*/


#ifndef RTYPE_ATEXTURE_HPP
#define RTYPE_ATEXTURE_HPP

#include <iostream>

namespace Engine {

    class ATexture {
    protected:
        std::string _filename;
    public:
        explicit ATexture(const std::string &file = "") : _filename(file) {};
        virtual ~ATexture() {}
        virtual void loadFromFile(std::string filename) = 0;
        [[nodiscard]] std::string getFilename() const {return this->_filename;}
    };

}

#endif //RTYPE_ATEXTURE_HPP
