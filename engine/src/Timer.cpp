//
// Created by mathi on 02/11/2020.
//

#include "Timer.hpp"

Engine::Timer::Timer() {}

double Engine::Timer::deltatime()
{
    auto now = std::chrono::high_resolution_clock::now();
    auto res = (double)(((now - this->_lastPoint) / std::chrono::milliseconds(1)) / 100.0);

    this->_lastPoint = std::chrono::high_resolution_clock::now();
    return res;
}

bool Engine::Timer::hasElapsed(std::chrono::high_resolution_clock::time_point time, double seconds)
{
    auto now = std::chrono::high_resolution_clock::now();

    return (((now - time) / std::chrono::milliseconds(1)) >= seconds * 1000);
}