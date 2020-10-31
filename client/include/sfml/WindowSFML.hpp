/*
** EPITECH PROJECT, 2020
** RType
** File description:
** Created by Cyprien
*/


#ifndef RTYPE_WINDOWSFML_HPP
#define RTYPE_WINDOWSFML_HPP

#include <Graphical/AWindow.hpp>
#include <SFML/Window.hpp>

class WindowSFML : public Engine::AWindow {
public:
    WindowSFML(const std::string &title, const std::pair<int, int> &windowSize) : Engine::AWindow(title, windowSize) {}

    void open() override;
    void display() override;
    void close() override;

private:
    std::unique_ptr<sf::Window> _window;
};


#endif //RTYPE_WINDOWSFML_HPP
