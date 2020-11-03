//
// Created by mathi on 29/10/2020.
//

#ifndef RTYPE_ENTITY_HPP
#define RTYPE_ENTITY_HPP

#include <memory>
#include <vector>
#include <iostream>
#include <map>
#include "ecs/Component.hpp"

namespace Engine {

    class Entity {

    protected:
        std::vector<std::unique_ptr<Component>> _components;

    public:
        explicit Entity() = default;

        template<typename T, typename... TArgs> void addComponent(TArgs&&... args);
        template<typename T> T *getComponent() const;

        bool hasComponents(std::vector<std::unique_ptr<Engine::Component>> &components)
        {
            size_t match = 0;

            for (auto &comp : components) {
                for (auto &my : this->_components) {
                    if (comp->getInfo() == my->getInfo()) {
                        match++;
                        break;
                    }
                }
            }
            return (match >= components.size());
        }
    };


    template<typename T, typename... TArgs>
    void Engine::Entity::addComponent(TArgs &&... args)
    {
        std::unique_ptr<Component> component = std::make_unique<T>(std::forward<TArgs>(args)...);

        component->setInfo(typeid(T).name());
        this->_components.push_back(std::move(component));
    }

    template<typename T>
    T *Engine::Entity::getComponent() const
    {
        for (auto &component : this->_components) {
            if (typeid(T).name() == component->getInfo())
                return static_cast<T *>(component.get());
        }
        return nullptr;
    }


}
#endif //RTYPE_ENTITY_HPP