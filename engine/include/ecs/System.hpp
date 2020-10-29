//
// Created by mathi on 29/10/2020.
//

#ifndef RTYPE_SYSTEM_HPP
#define RTYPE_SYSTEM_HPP

#include <vector>
#include <memory>
#include "Entity.hpp"

namespace Engine {

    class System {

    protected:
        std::vector<std::unique_ptr<Component>> _dependencies;
        std::vector<std::reference_wrapper<std::unique_ptr<Entity>>> _entities;

    public:
        explicit System() = default;

        template<typename T>
        void addDependency();

        void addEntity(std::unique_ptr <Entity> &entity);

        std::vector <std::unique_ptr<Component>> &getDependencies();

        std::vector<std::reference_wrapper<std::unique_ptr<Entity>>> &getEntities();

        virtual void update() = 0;
    };

}

#endif //RTYPE_SYSTEM_HPP
