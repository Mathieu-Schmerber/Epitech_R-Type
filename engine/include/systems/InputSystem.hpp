//
// Created by mathi on 01/11/2020.
//

#ifndef RTYPE_INPUTSYSTEM_HPP
#define RTYPE_INPUTSYSTEM_HPP

#include "graphical/AEvents.hpp"
#include "ecs/System.hpp"

namespace Engine {

    class InputSystem : public Engine::System {
    private:
        Engine::AEvents *_events;

    public:
        explicit InputSystem(Engine::AEvents *events);

        void update() override;
    };
}

#endif //RTYPE_INPUTSYSTEM_HPP