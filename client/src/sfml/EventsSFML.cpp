/*
** EPITECH PROJECT, 2020
** RType
** File description:
** Created by Cyprien
*/


#include <iostream>
#include "sfml/EventsSFML.hpp"

void EventsSFML::update() {
    _released.clear();

    while (_window->getWindow()->pollEvent(_event)) {
        switch (_event.type) {
            case sf::Event::Closed:
                _windowClosed = true;
                break;

            case sf::Event::KeyPressed:
                std::cout << _event.key.code << " Pressed" << std::endl;
                if (!isInVector(_pressed, static_cast<Engine::Key>(_event.key.code)))
                    _pressed.push_back(static_cast<Engine::Key>(_event.key.code));
                break;

            case sf::Event::KeyReleased:
                std::cout << _event.key.code << " Released" << std::endl;
                _released.push_back(static_cast<Engine::Key>(_event.key.code));
                removeInVector(_pressed, static_cast<Engine::Key>(_event.key.code));
                break;

            default:
                break;
        }
    }
}