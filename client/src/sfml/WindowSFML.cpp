/*
** EPITECH PROJECT, 2020
** RType
** File description:
** Created by Cyprien
*/

#include "sfml/WindowSFML.hpp"

void WindowSFML::open()
{
    _window = std::make_unique<sf::Window>(sf::VideoMode(_size.first, _size.second), _title);
}

void WindowSFML::display()
{
    //_window->clear(sf::Color::Black);
    _window->display();
}

void WindowSFML::close()
{
    _window->close();
}
