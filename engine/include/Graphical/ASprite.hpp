//
// Created by mathi on 30/10/2020.
//

#ifndef RTYPE_ASPRITE_HPP
#define RTYPE_ASPRITE_HPP

#include <utility>
#include "tools/Geometry.hpp"

namespace Engine {

    class ASprite {
    private:
        Point<int> _size;
    public:
        explicit ASprite();

        ~ASprite() = default;

        Point<int> getSize();
        //TODO: Write virtual functions to override
        //TODO: example: Draw, createFromFile......
    };

}

#endif //RTYPE_ASPRITE_HPP