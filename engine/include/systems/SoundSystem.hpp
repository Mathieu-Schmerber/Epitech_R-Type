//
// Created by mathi on 15/11/2020.
//

#ifndef RTYPE_SOUNDSYSTEM_HPP
#define RTYPE_SOUNDSYSTEM_HPP

#include "ecs/System.hpp"

namespace Engine {
    class SoundSystem : public Engine::System {
    public:
        SoundSystem();

        void update() override;
    };
}

#endif //RTYPE_SOUNDSYSTEM_HPP
