/*
** EPITECH PROJECT, 2020
** RType
** File description:
** Created by Cyprien
*/


#ifndef RTYPE_GRAPHICALSFML_HPP
#define RTYPE_GRAPHICALSFML_HPP

#include <Graphical/AGraphical.hpp>
#include <Graphical/AWindow.hpp>
#include <Graphical/ASound.hpp>
#include <Graphical/AEvents.hpp>
#include <memory>

class GraphicalSFML : public Engine::AGraphical {
public:
    GraphicalSFML() = default;
    GraphicalSFML(std::unique_ptr<Engine::AWindow> window, std::unique_ptr<Engine::ASound> sound, std::unique_ptr<Engine::AEvents> events) : _window(std::move(window)), _sound(std::move(sound)), _events(std::move(events)) {};

    void setWindow(std::unique_ptr<Engine::AWindow> window);
    void setSound(std::unique_ptr<Engine::ASound> sound);
    void setEvents(std::unique_ptr<Engine::AEvents> events);

private:
    std::unique_ptr<Engine::AWindow> _window = nullptr;
    std::unique_ptr<Engine::ASound> _sound = nullptr;
    std::unique_ptr<Engine::AEvents> _events = nullptr;
};


#endif //RTYPE_GRAPHICALSFML_HPP
