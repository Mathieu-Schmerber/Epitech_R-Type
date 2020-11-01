//
// Created by mathi on 01/11/2020.
//

#ifndef RTYPE_PHYSICSYSTEM_HPP
#define RTYPE_PHYSICSYSTEM_HPP

#include "ecs/System.hpp"

namespace Engine {

class PhysicSystem : public Engine::System {
    public:
        explicit PhysicSystem();

        void update() override;
    };

}

#endif //RTYPE_PHYSICSYSTEM_HPP
