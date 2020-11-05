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
    _window->display();
    _window->clear(sf::Color::Black);
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

std::unique_ptr<sf::RenderWindow> &WindowSFML::getWindow()
{
    return _window;
}

void WindowSFML::setFrameRate(int frameRate)
{
    _frameRate = frameRate;
    _window->setFramerateLimit(frameRate);
}

bool WindowSFML::getVsync() const
{
    return _vSyncEnabled;
}

void WindowSFML::setVsync(bool sync)
{
    _vSyncEnabled = sync;
}

int WindowSFML::getFrameRate() const
{
    return _frameRate;
}
