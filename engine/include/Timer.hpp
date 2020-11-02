//
// Created by mathi on 02/11/2020.
//

#ifndef RTYPE_TIMER_HPP
#define RTYPE_TIMER_HPP

#include <chrono>

namespace Engine {

    class Timer {
    private:
        std::chrono::high_resolution_clock::time_point _startPoint;
        std::chrono::high_resolution_clock::time_point _lastPoint;

    public:
        Timer();
        ~Timer() = default;

        double deltatime();
        bool hasElapsed(float seconds);
        void restart();
    };

}

#endif //RTYPE_TIMER_HPP
