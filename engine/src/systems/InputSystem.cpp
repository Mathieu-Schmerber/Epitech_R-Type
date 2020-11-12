//
// Created by mathi on 01/11/2020.
//

#include "components/ControllerComponent.hpp"
#include "systems/InputSystem.hpp"

Engine::InputSystem::InputSystem(Engine::AEvents *events) : _events(events), Engine::System()
{
    this->addDependency<ControllerComponent>();
}

void Engine::InputSystem::update()
{
    for (auto &e : this->_entities) {
        auto controller = e->getComponent<ControllerComponent>();
        controller->setPressed(this->_events->getKeysPressed());
        controller->setReleased(this->_events->getKeysReleased());
    }
}