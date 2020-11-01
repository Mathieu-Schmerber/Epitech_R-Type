/*
** EPITECH PROJECT, 2020
** RType
** File description:
** Created by Cyprien
*/

#include "sfml/WindowSFML.hpp"

void WindowSFML::open()
{
    _window = std::make_unique<sf::RenderWindow>(sf::VideoMode(_size.first, _size.second), _titleSFML);
}

void WindowSFML::display()
{
    _window->clear(sf::Color::Black);
    _window->display();
}

bool WindowSFML::isOpen()
{
    return _window->isOpen();
}

void WindowSFML::close()
{
    _window->close();
}

void WindowSFML::setTitle(const std::string &title)
{
    AWindow::setTitle(title);
    _titleSFML = sf::String(title.data());
}

//void WindowSFML::draw(Engine::ASprite &)
//{
//
//}
//
std::unique_ptr<sf::RenderWindow> &WindowSFML::getWindow()
{
    return _window;
}
