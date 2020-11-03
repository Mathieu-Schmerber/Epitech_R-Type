//
// Created by mathi on 02/11/2020.
//

#include "Timer.hpp"

Engine::Timer::Timer() :_startPoint(std::chrono::high_resolution_clock::now()) {}

double Engine::Timer::deltatime()
{
    auto now = std::chrono::high_resolution_clock::now();
    auto res = (double)(((now - this->_lastPoint) / std::chrono::milliseconds(1)) / 100.0);

    this->_lastPoint = std::chrono::high_resolution_clock::now();
    return res;
}

void Engine::Timer::restart()
{
    this->_startPoint = std::chrono::high_resolution_clock::now();
    this->_lastPoint = this->_startPoint;
}

