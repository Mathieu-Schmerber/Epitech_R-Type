//
// Created by mathi on 06/11/2020.
//

#ifndef RTYPE_MOVESYSTEM_HPP
#define RTYPE_MOVESYSTEM_HPP

#include "ecs/System.hpp"

namespace Engine {

    class MoveSystem : public Engine::System {
    public:
        MoveSystem();

        void update() override;
    };

}

#endif //RTYPE_MOVESYSTEM_HPP
