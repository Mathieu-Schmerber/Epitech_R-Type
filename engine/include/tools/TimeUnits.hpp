/*
** EPITECH PROJECT, 2020
** RType
** File description:
** Created by Cyprien
*/


#ifndef RTYPE_TIMEUNITS_HPP
#define RTYPE_TIMEUNITS_HPP

#include <cstdint>

/*** DEPRECATED ***/

class Time;

namespace Engine {

    struct seconds {
    public:
        seconds() = delete;
        explicit seconds(double seconds) : _seconds(seconds) {}
    private:
        double _seconds;
        friend class Time;
    };
    struct milliseconds {
    public:
        milliseconds() = delete;
        explicit milliseconds(int32_t milliseconds) : _milliseconds(milliseconds) {}
    private:
        int32_t _milliseconds;
        friend class Time;
    };
    struct microseconds {
    public:
        microseconds() = delete;
        explicit microseconds(int64_t microseconds) : _microseconds(microseconds) {}
    private:
        int64_t _microseconds;
        friend class Time;
    };


}

#endif //RTYPE_TIMEUNITS_HPP
