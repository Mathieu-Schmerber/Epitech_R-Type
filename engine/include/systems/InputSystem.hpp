//
// Created by mathi on 01/11/2020.
//

#ifndef RTYPE_INPUTSYSTEM_HPP
#define RTYPE_INPUTSYSTEM_HPP

#include "AWindow.hpp"
#include "ecs/System.hpp"

namespace Engine {

    class InputSystem : public Engine::System {
    private:
        Engine::AWindow *_window;

    public:
        explicit InputSystem(Engine::AWindow *window);

        void update() override;
    };
}

#endif //RTYPE_INPUTSYSTEM_HPP
