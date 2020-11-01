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
    GraphicalSFML(std::unique_ptr<Engine::AWindow> window, std::unique_ptr<Engine::ASound> sound, std::unique_ptr<Engine::AEvents> events) :
    Engine::AGraphical(std::move(window), std::move(sound), std::move(events)) {};
};


#endif //RTYPE_GRAPHICALSFML_HPP
