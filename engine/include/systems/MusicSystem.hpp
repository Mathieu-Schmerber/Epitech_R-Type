//
// Created by mathi on 15/11/2020.
//

#ifndef RTYPE_MUSICSYSTEM_HPP
#define RTYPE_MUSICSYSTEM_HPP

#include "ecs/System.hpp"

namespace Engine {
    class MusicSystem : public Engine::System {
    public:
        MusicSystem();

        void update() override;
    };
}

#endif //RTYPE_MUSICSYSTEM_HPP