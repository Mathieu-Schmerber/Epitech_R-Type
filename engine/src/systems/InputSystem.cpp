//
// Created by mathi on 01/11/2020.
//

#include "components/ControllerComponent.hpp"
#include "systems/InputSystem.hpp"

Engine::InputSystem::InputSystem(Engine::AWindow *window) : _window(window), Engine::System()
{
    this->addDependency<ControllerComponent>();
}

void Engine::InputSystem::update()
{
    for (auto &e : this->_entities) {
        auto controller = e.get()->getComponent<ControllerComponent>();

        /*
        TODO:
            controller->releaseAll();
            for (auto &input : this->_window->getKeyPressed())
                controller->press(input);
        */
    }
}