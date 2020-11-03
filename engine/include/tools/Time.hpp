/*
** EPITECH PROJECT, 2020
** RType
** File description:
** Created by Cyprien
*/


#ifndef RTYPE_TIME_HPP
#define RTYPE_TIME_HPP

#include <cstdint>
#include <type_traits>
#include "tools/TimeUnits.hpp"
#include "tools/ATime.hpp"

/*** DEPRECATED ***/

namespace Engine {

    template<typename T, std::enable_if<
            std::is_same<T, seconds>::value ||
            std::is_same<T, milliseconds>::value ||
            std::is_same<T, microseconds>::value>>
    class Time : public ATime {
    private:
        T _unit;

        template<std::enable_if<std::is_same<T, seconds>::value>>
        float toSeconds() {return _unit._seconds;};
        template<std::enable_if<std::is_same<T, milliseconds>::value>>
        float toSeconds() {return 0;};
        template<std::enable_if<std::is_same<T, microseconds>::value>>
        float toSeconds() {return 0;};

    public:
        Time(int e) : _unit(e) {}
        float asSeconds() override {
            return toSeconds();
        }
    };

}

#endif //RTYPE_TIME_HPP
