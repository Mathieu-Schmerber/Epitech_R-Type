//
// Created by mathi on 02/11/2020.
//

#include "tools/Timer.hpp"

Engine::Timer::Timer() : _lastPoint(std::chrono::high_resolution_clock::now()) {}

double Engine::Timer::deltatime(double multiplier)
{
    auto now = std::chrono::high_resolution_clock::now();
    auto res = std::chrono::duration<double, std::milli>(now - this->_lastPoint).count() * multiplier;

    this->_lastPoint = std::chrono::high_resolution_clock::now();
    return res;
}

bool Engine::Timer::hasElapsed(std::chrono::high_resolution_clock::time_point time, double seconds)
{
    auto now = std::chrono::high_resolution_clock::now();

    return (((now - time) / std::chrono::milliseconds(1)) >= seconds * 1000);
}

double Engine::Timer::getElapsed(std::chrono::high_resolution_clock::time_point time)
{
    auto now = std::chrono::high_resolution_clock::now();
    auto res = std::chrono::duration<double, std::milli>(now - time).count();

    return res;
}

const std::chrono::high_resolution_clock::time_point &Engine::Timer::getLastPoint() const
{
    return _lastPoint;
}