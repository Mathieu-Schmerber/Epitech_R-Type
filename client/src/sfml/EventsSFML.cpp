/*
** EPITECH PROJECT, 2020
** RType
** File description:
** Created by Cyprien
*/


#include "sfml/EventsSFML.hpp"

void EventsSFML::update() {
    _keyReleased.clear();
    _buttonsReleased.clear();
    _scroll.movement = 0;

    while (_window->getWindow()->pollEvent(_event)) {
        manageEvents();
    }
}

void EventsSFML::manageEvents()
{
    switch (_event.type) {
        /** Window Closed **/
        case sf::Event::Closed:
            _window->getWindow()->close(); // FIXME On le laisse là ?
            break;

        /** Key Pressed **/
        case sf::Event::KeyPressed:
            if (!isInVector(_keyPressed, static_cast<Engine::Inputs>(_event.key.code)))
                _keyPressed.push_back(static_cast<Engine::Inputs>(_event.key.code));
            break;

        /** Key Released **/
        case sf::Event::KeyReleased:
            _keyReleased.push_back(static_cast<Engine::Inputs>(_event.key.code));
            removeInVector(_keyPressed, static_cast<Engine::Inputs>(_event.key.code));
            break;

        /** Mouse Button Pressed **/
        case sf::Event::MouseButtonPressed:
            if (!isInVector(_buttonsPressed, _mouseLink.at(_event.mouseButton.button)))
                _buttonsPressed.push_back(_mouseLink.at(_event.mouseButton.button));
            _mousePos = {_event.mouseButton.x, _event.mouseButton.y};
            break;

        /** Mouse Button Released **/
        case sf::Event::MouseButtonReleased:
            _buttonsReleased.push_back(_mouseLink.at(_event.mouseButton.button));
            removeInVector(_buttonsPressed, _mouseLink.at(_event.mouseButton.button));
            _mousePos = {_event.mouseButton.x, _event.mouseButton.y};
            break;

        /** Mouse Wheel Scrolled **/
        case sf::Event::MouseWheelScrolled:
            if (_event.mouseWheelScroll.wheel == sf::Mouse::VerticalWheel)
                _scroll.direction = Engine::Scroll::vertical;
            else if (_event.mouseWheelScroll.wheel == sf::Mouse::HorizontalWheel)
                _scroll.direction = Engine::Scroll::horizontal;
            else
                std::cerr << "wheel movement type: unknown" << std::endl;
            _scroll.movement = _event.mouseWheelScroll.delta;
            _mousePos = {_event.mouseWheelScroll.x, _event.mouseWheelScroll.y};

        /** Mouse Moved **/
        case sf::Event::MouseMoved:
            _mousePos = {_event.mouseMove.x, _event.mouseMove.y};

        /** Mouse Entered In Window **/
        case sf::Event::MouseEntered:
            _mouseInWindow = true;

        /** Mouse Left The Window **/
        case sf::Event::MouseLeft:
            _mouseInWindow = false;

        default:
            break;
    }
}

Engine::Point<int> EventsSFML::getMousePos()
{
    return {sf::Mouse::getPosition().x, sf::Mouse::getPosition().y};
}

bool EventsSFML::isButtonPressed(Engine::Mouse button)
{
    return sf::Mouse::isButtonPressed(static_cast<sf::Mouse::Button>(_mouseRvLink.at(button)));
}
