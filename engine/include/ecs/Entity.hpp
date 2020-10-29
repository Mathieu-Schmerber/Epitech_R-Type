//
// Created by mathi on 29/10/2020.
//

#ifndef RTYPE_ENTITY_HPP
#define RTYPE_ENTITY_HPP

#include <memory>
#include <vector>
#include "Component.hpp"

namespace Engine {

    class Entity {

    protected:
        std::vector <std::unique_ptr<Component>> _components;

    public:
        explicit Entity() = default;

        template<typename T, typename... TArgs>
        void addComponent(TArgs &&... args);

        template<typename T>
        T *getComponent();

        bool hasComponents(std::vector <std::unique_ptr<Component>> &components);
    };
}
#endif //RTYPE_ENTITY_HPP