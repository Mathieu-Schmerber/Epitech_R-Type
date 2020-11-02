//
// Created by mathi on 02/11/2020.
//

#include "Timer.hpp"

Engine::Timer::Timer() :_startPoint(std::chrono::high_resolution_clock::now()) {}

double Engine::Timer::deltatime()
{
    auto now = std::chrono::high_resolution_clock::now();
    auto res = (double)(((now - this->_startPoint) / std::chrono::milliseconds(1)) / 100.0);

    this->restart();
    return res;
}

bool Engine::Timer::hasElapsed(float seconds)
{
    return (this->deltatime() >= seconds * 1000);
}

void Engine::Timer::restart()
{
    this->_startPoint = std::chrono::high_resolution_clock::now();
    this->_lastPoint = this->_startPoint;
}

