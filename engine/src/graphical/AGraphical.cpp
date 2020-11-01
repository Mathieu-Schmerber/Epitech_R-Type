/*
** EPITECH PROJECT, 2020
** RType
** File description:
** Created by Cyprien
*/


#include "graphical/AGraphical.hpp"

void Engine::AGraphical::setWindow(std::shared_ptr<Engine::AWindow> window)
{
    _window = std::move(window);
}

void Engine::AGraphical::setSound(std::shared_ptr<Engine::ASound> sound)
{
    _sound = std::move(sound);
}

void Engine::AGraphical::setEvents(std::shared_ptr<Engine::AEvents> events)
{
    _events = std::move(events);
}
