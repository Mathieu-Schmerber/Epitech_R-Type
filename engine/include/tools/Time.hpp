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

namespace  Engine {

    struct seconds {
    public:
        seconds() = delete;
        explicit seconds(float seconds) : _seconds(seconds) {}
    private:
        float _seconds;
    };
    struct milliseconds {
    public:
        milliseconds() = delete;
        explicit milliseconds(int32_t milliseconds) : _milliseconds(milliseconds) {}
    private:
        int32_t _milliseconds;
    };
    struct microseconds {
    public:
        microseconds() = delete;
        explicit microseconds(int64_t microseconds) : _microseconds(microseconds) {}
    private:
        int64_t _microseconds;
    };

    class ATime {
    public:
        float asSeconds() {return 0;}
    private:
        ATime() = default;
        friend class Time;
    };

    /*template<typename T, std::enable_if<
            std::is_same<T, seconds>::value ||
            std::is_same<T, milliseconds>::value ||
            std::is_same<T, microseconds>::value>>
    class Time : public ATime {
    private:
        T _unit;

        seconds toSeconds()
    };*/

}

#endif //RTYPE_TIME_HPP
