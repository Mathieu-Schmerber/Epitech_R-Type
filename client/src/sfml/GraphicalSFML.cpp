/*
** EPITECH PROJECT, 2020
** RType
** File description:
** Created by Cyprien
*/


#include "sfml/GraphicalSFML.hpp"

void GraphicalSFML::setWindow(std::unique_ptr<Engine::AWindow> window)
{
    _window = std::move(window);
}

void GraphicalSFML::setSound(std::unique_ptr<Engine::ASound> sound)
{
    _sound = std::move(sound);
}

void GraphicalSFML::setEvents(std::unique_ptr<Engine::AEvents> events)
{
    _events = std::move(events);
}