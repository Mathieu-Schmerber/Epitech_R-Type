/*
** EPITECH PROJECT, 2020
** RType
** File description:
** Created by Cyprien
*/


#ifndef RTYPE_ATIME_HPP
#define RTYPE_ATIME_HPP

/*** DEPRECATED ***/

class Time;

namespace Engine {

    class ATime {
    public:
        virtual float asSeconds() = 0;
    private:
        ATime() = default;
        friend class Time;
    };

}

#endif //RTYPE_ATIME_HPP
