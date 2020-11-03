//
// Created by mathi on 30/10/2020.
//

#ifndef RTYPE_DRAWSYSTEM_HPP
#define RTYPE_DRAWSYSTEM_HPP

#include "graphical/AWindow.hpp"
#include "ecs/System.hpp"

namespace Engine {

    class DrawSystem : public Engine::System {

    private:
        std::shared_ptr<Engine::AWindow> _window;

        [[nodiscard]] static bool compare(const std::shared_ptr<Engine::Entity> &a, const std::shared_ptr<Engine::Entity> &b);
    public:
        explicit DrawSystem(std::shared_ptr<Engine::AWindow> &window);
        void update() override;
    };

}

#endif //RTYPE_DRAWSYSTEM_HPP
