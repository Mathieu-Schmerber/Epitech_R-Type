/*
** EPITECH PROJECT, 2020
** RType
** File description:
** Created by Cyprien
*/

#include "tools/Geometry.hpp"
#include "sfml/WindowSFML.hpp"

void WindowSFML::open()
{
    Engine::Size<unsigned int> convert = {(unsigned int)_size.x, (unsigned int)_size.y};
    _window = std::make_unique<sf::RenderWindow>(sf::VideoMode(convert.x, convert.y), _titleSFML);
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

Engine::Size<double> WindowSFML::getSize() const
{
    if (!_window)
        return this->_size;
    return {static_cast<double>(this->_window->getSize().x), static_cast<double>(this->_window->getSize().y)};
}