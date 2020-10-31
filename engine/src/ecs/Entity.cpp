//
// Created by mathi on 29/10/2020.
//

#include "ecs/Entity.hpp"

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
        if (reinterpret_cast<T>(component))
            return component;
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
    return (match >= components.size());
}