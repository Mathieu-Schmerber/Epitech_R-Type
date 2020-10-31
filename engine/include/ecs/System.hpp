//
// Created by mathi on 29/10/2020.
//

#ifndef RTYPE_SYSTEM_HPP
#define RTYPE_SYSTEM_HPP

#include <vector>
#include <memory>
#include "ecs/Entity.hpp"

namespace Engine {

    class System {

    protected:
        std::vector<std::unique_ptr<Component>> _dependencies;
        std::vector<std::reference_wrapper<std::unique_ptr<Entity>>> _entities;

    public:
        explicit System() = default;

        template<typename T> void addDependency();

        void addEntity(std::unique_ptr<Engine::Entity> &entity)
        {
            this->_entities.emplace_back(entity);
        }


        std::vector <std::unique_ptr<Component>> &getDependencies()
        {
            return this->_dependencies;
        }

        std::vector<std::reference_wrapper<std::unique_ptr<Entity>>> &getEntities()
        {
            return this->_entities;
        }
        virtual void update() = 0;
    };

    template<typename T> void Engine::System::addDependency() {
        std::unique_ptr<Component> component = std::make_unique<T>();

        component->setInfo(typeid(T).name());
        this->_dependencies.push_back(std::move(component));
    }



}

#endif //RTYPE_SYSTEM_HPP
