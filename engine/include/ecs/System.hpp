//
// Created by mathi on 29/10/2020.
//

#ifndef RTYPE_SYSTEM_HPP
#define RTYPE_SYSTEM_HPP

#include <vector>
#include <memory>
#include "tools/Utils.hpp"
#include "ecs/Entity.hpp"

namespace Engine {

    class System {

    private:
        float _deltatime;

    protected:
        std::vector<std::unique_ptr<Component>> _dependencies;
        std::vector<std::shared_ptr<Entity>> _entities;

    public:
        explicit System() : _deltatime(0) {}

        void setDeltatime(float delta) {this->_deltatime = delta;}
        [[nodiscard]] float deltatime() const {return this->_deltatime;}

        template<typename T> void addDependency();

        void addEntity(std::shared_ptr<Engine::Entity> &entity)
        {
            this->_entities.emplace_back(entity);
        }

        virtual void deleteEntity(std::shared_ptr<Engine::Entity> &entity)
        {
            Utils::removeFromVector(this->_entities, entity);
        }

        std::vector <std::unique_ptr<Component>> &getDependencies()
        {
            return this->_dependencies;
        }

        std::vector<std::shared_ptr<Entity>> &getEntities()
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
