//
// Created by mathi on 29/10/2020.
//

#include "Graphical/AWindow.hpp"

Engine::AWindow::AWindow(const std::string &title, const std::pair<int, int> &windowSize)
: _title(title), _size(windowSize) {}

void Engine::AWindow::open()
{
}

void Engine::AWindow::display()
{
}

void Engine::AWindow::close()
{
}

void Engine::AWindow::setSize(const std::pair<int, int> &size)
{
    this->_size = size;
}

void Engine::AWindow::setTitle(const std::string &title)
{
    this->_title = title;
}

std::pair<int, int> Engine::AWindow::getSize() const
{
    return this->_size;
}

std::string Engine::AWindow::getTitle() const
{
    return this->_title;
}
