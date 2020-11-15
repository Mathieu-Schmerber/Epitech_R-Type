/*
** EPITECH PROJECT, 2020
** RType
** File description:
** Created by Cyprien
*/


#ifndef RTYPE_AGRAPHICAL_HPP
#define RTYPE_AGRAPHICAL_HPP

#include <memory>
#include "AWindow.hpp"
#include "ASound.hpp"
#include "AEvents.hpp"

namespace Engine {

    class AGraphical {
    public:
        AGraphical() = default;
        AGraphical(std::unique_ptr<Engine::AWindow> window, std::unique_ptr<Engine::AEvents> events) :
        _window(std::move(window)), _events(std::move(events)) {};

        virtual void setWindow(std::shared_ptr<Engine::AWindow> window);
        virtual void setEvents(std::shared_ptr<Engine::AEvents> events);

        std::shared_ptr<Engine::AWindow> &getWindow() {return _window;};
        std::shared_ptr<Engine::AEvents> &getEvents() {return _events;};

    protected:
        std::shared_ptr<Engine::AWindow> _window = nullptr;
        std::shared_ptr<Engine::AEvents> _events = nullptr;
    };

}
#endif //RTYPE_AGRAPHICAL_HPP
