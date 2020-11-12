//
// Created by mathi on 02/11/2020.
//

#include "tools/Timer.hpp"

Engine::Timer::Timer() : _lastPoint(std::chrono::high_resolution_clock::now()) {}

float Engine::Timer::deltatime(float multiplier)
{
    auto now = std::chrono::high_resolution_clock::now();
    auto res = std::chrono::duration<float, std::milli>(now - this->_lastPoint).count() * multiplier;

    this->_lastPoint = std::chrono::high_resolution_clock::now();
    return res;
}

bool Engine::Timer::hasElapsed(std::chrono::high_resolution_clock::time_point time, float seconds)
{
    auto now = std::chrono::high_resolution_clock::now();

    return (((now - time) / std::chrono::milliseconds(1)) >= seconds * 1000);
}

const std::chrono::high_resolution_clock::time_point &Engine::Timer::getLastPoint() const
{
    return _lastPoint;
}