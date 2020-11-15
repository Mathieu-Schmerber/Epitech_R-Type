//
// Created by mathi on 15/11/2020.
//

#ifndef RTYPE_SOUNDSYSTEM_HPP
#define RTYPE_SOUNDSYSTEM_HPP

#include "ecs/System.hpp"
#include "graphical/AWindow.hpp"

namespace Engine {
    class SoundSystem : public Engine::System {
    private:
        std::shared_ptr<AWindow> _window;
    public:
        SoundSystem(std::shared_ptr<AWindow> &window);

        void update() override;
    };
}

#endif //RTYPE_SOUNDSYSTEM_HPP
