/*
** EPITECH PROJECT, 2020
** RType
** File description:
** Created by Cyprien
*/


#ifndef RTYPE_AFONT_HPP
#define RTYPE_AFONT_HPP

#include <iostream>

namespace Engine {

    class AFont {
    public:
        AFont() = default;
        virtual void loadFromFile(std::string file) = 0;
        [[nodiscard]] virtual std::string getFileName() const = 0;
    };

}


#endif //RTYPE_AFONT_HPP
