//
// Created by mathi on 29/10/2020.
//

#ifndef RTYPE_ENTITY_HPP
#define RTYPE_ENTITY_HPP

#include <memory>
#include <vector>
#include <iostream>
#include "ecs/Component.hpp"

namespace Engine {

    class Entity {

    protected:
        std::vector<std::unique_ptr<Component>> _components;

    public:
        explicit Entity() = default;

        template<typename T, typename... TArgs> void addComponent(TArgs&&... args);
        template<typename T> T *getComponent();
        bool hasComponents(std::vector<std::unique_ptr<Component>> &components);
    };


    template<typename T, typename... TArgs>
    void Engine::Entity::addComponent(TArgs &&... args)
    {
        auto component = std::make_unique<T>(std::forward<TArgs>(args)...);

        this->_components.push_back(std::move(component));
    }

    template<typename T>
    T *Engine::Entity::getComponent()
    {
        for (auto &component : this->_components) {
            if (typeid(component) == typeid(T))
                return static_cast<T *>(component.get());
        }
        return nullptr;
    }

    bool Engine::Entity::hasComponents(std::vector<std::unique_ptr<Engine::Component>> &components) {
        size_t match = 0;

        for (auto &comp : components) {
            for (auto &my : this->_components) {
                if (typeid(my) == typeid(comp)) {
                    match++;
                    break;
                }
            }
        }
        std::cout << "matching: " << match << std::endl;
        return (match >= components.size());
    }
}
#endif //RTYPE_ENTITY_HPP