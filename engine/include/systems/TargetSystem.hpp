//
// Created by mathi on 13/11/2020.
//

#ifndef RTYPE_CHILDRENSYSTEM_HPP
#define RTYPE_CHILDRENSYSTEM_HPP

#include "ecs/System.hpp"

namespace Engine {
    class TargetSystem : public Engine::System
    {
    public:
        TargetSystem();

        void deleteEntity(std::shared_ptr<Engine::Entity> &entity) override;
    };
}

#endif //RTYPE_CHILDRENSYSTEM_HPP
