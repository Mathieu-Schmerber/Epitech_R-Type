/*
** EPITECH PROJECT, 2020
** RType
** File description:
** Created by Cyprien
*/


#ifndef RTYPE_EVENTSSFML_HPP
#define RTYPE_EVENTSSFML_HPP

#include "graphical/AEvents.hpp"
#include "sfml/WindowSFML.hpp"
#include <SFML/Window/Event.hpp>
#include <memory>
#include <map>

template<typename T, typename U>
std::map<U, T> reverseMap(std::map<T, U> map)
{
    std::map<U, T> rv;

    for (auto &e : map)
        rv[e.second] = e.first;
    return rv;
}

class EventsSFML : public Engine::AEvents {
public:
    EventsSFML(std::shared_ptr<Engine::AWindow> &window) : Engine::AEvents(), _window(std::dynamic_pointer_cast<WindowSFML>(window)),
    _mouseRvLink(reverseMap(_mouseLink)) {}
    void update();

    bool isButtonPressed(Engine::Mouse button) override;
    Engine::Point<int> getMousePos() override;


private:
    std::shared_ptr<WindowSFML> _window;
    sf::Event _event;

    std::map<sf::Mouse::Button, Engine::Mouse> _mouseLink = {
            {sf::Mouse::Right, Engine::Mouse::right},
            {sf::Mouse::Left, Engine::Mouse::left},
            {sf::Mouse::Middle, Engine::Mouse::middle},
            {sf::Mouse::XButton1, Engine::Mouse::extra1},
            {sf::Mouse::XButton2, Engine::Mouse::extra2}
    };
    std::map<Engine::Mouse, sf::Mouse::Button> _mouseRvLink;

    void manageEvents();
};

template<typename T>
std::basic_ostream<char> &operator<<(std::basic_ostream<char> &c, std::vector<T> vector)
{
    for (auto &i : vector)
        c << i << " ";
    return c;
}

#endif //RTYPE_EVENTSSFML_HPP
