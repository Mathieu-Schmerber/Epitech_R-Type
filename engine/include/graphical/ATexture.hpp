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
        virtual void loadFromFile(std::string filename) = 0;
    };

}

#endif //RTYPE_ATEXTURE_HPP
