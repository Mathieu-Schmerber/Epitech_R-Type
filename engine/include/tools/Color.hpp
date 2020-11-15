/*
** EPITECH PROJECT, 2020
** RType
** File description:
** Created by Cyprien
*/


#ifndef RTYPE_COLOR_HPP
#define RTYPE_COLOR_HPP

#include <ostream>

namespace Engine {

    struct Color {
        unsigned char red;
        unsigned char green;
        unsigned char blue;
        unsigned char alpha;
    };

    inline std::ostream& operator<<(std::ostream& os, Engine::Color c) {
        return os << "red: " << static_cast<int>(c.red) << " green: " << static_cast<int>(c.green) << " blue: " << static_cast<int>(c.blue) << " alpha: " << static_cast<int>(c.alpha);
    }
}

#endif //RTYPE_COLOR_HPP
