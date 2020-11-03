//
// Created by mathi on 03/11/2020.
//

#ifndef RTYPE_AENTITYGROUP_HPP
#define RTYPE_AENTITYGROUP_HPP

#include "ecs/Entity.hpp"

namespace Engine {

    class AEntityGroup
    {
    private:
        std::vector<std::shared_ptr<Engine::Entity>> _entities;

    public:
        AEntityGroup();
        ~AEntityGroup();

        virtual void freeze();
        virtual void unFreeze();
        void addEntity(std::shared_ptr<Engine::Entity> &entity);
        void addEntities(const std::vector<std::shared_ptr<Engine::Entity>> &entities);
        std::vector<std::shared_ptr<Engine::Entity>> getEntities() const;
    };

}

#endif //RTYPE_AENTITYGROUP_HPP
