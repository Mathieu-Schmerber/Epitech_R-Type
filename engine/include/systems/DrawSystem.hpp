//
// Created by mathi on 30/10/2020.
//

#ifndef RTYPE_DRAWSYSTEM_HPP
#define RTYPE_DRAWSYSTEM_HPP

#include "AWindow.hpp"
#include "ecs/System.hpp"

namespace Engine {

    class DrawSystem : public Engine::System {

    private:
        Engine::AWindow *_window;

    public:
        explicit DrawSystem(Engine::AWindow *window);
        void update() override;
    };

}

#endif //RTYPE_DRAWSYSTEM_HPP
