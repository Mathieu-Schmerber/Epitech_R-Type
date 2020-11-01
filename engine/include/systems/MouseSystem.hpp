//
// Created by mathi on 01/11/2020.
//

#ifndef RTYPE_MOUSESYSTEM_HPP
#define RTYPE_MOUSESYSTEM_HPP

#include "ecs/System.hpp"
#include "Graphical/AWindow.hpp"

namespace Engine {

    class MouseSystem : public Engine::System {
    private:
        Engine::AWindow *_window;

    public:
        explicit MouseSystem(Engine::AWindow *window);

        void update() override;
    };
}

#endif //RTYPE_MOUSESYSTEM_HPP
