//
// Created by mathi on 02/11/2020.
//

#ifndef RTYPE_PARALLAXSYSTEM_HPP
#define RTYPE_PARALLAXSYSTEM_HPP

#include "graphical/AWindow.hpp"
#include "ecs/System.hpp"

namespace Engine {

    class ParallaxSystem : public Engine::System {
    private:
        std::shared_ptr<AWindow> _window;
    public:
        explicit ParallaxSystem();

        void update() override;
    };

}

#endif //RTYPE_PARALLAXSYSTEM_HPP
