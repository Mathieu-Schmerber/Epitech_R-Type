//
// Created by mathi on 01/11/2020.
//

#ifndef RTYPE_MOUSESYSTEM_HPP
#define RTYPE_MOUSESYSTEM_HPP

#include "ecs/System.hpp"
#include "graphical/AEvents.hpp"

namespace Engine {

    class MouseSystem : public Engine::System {
    private:
        std::shared_ptr<Engine::AEvents> _events;

    public:
        explicit MouseSystem(std::shared_ptr<Engine::AEvents> &events);

        void update() override;
    };
}

#endif //RTYPE_MOUSESYSTEM_HPP
