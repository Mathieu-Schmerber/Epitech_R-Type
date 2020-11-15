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

    /*!
     * @brief Describes an Entity
     */
    class Entity {

    protected:
        std::vector<std::unique_ptr<Component>> _components;

    public:
        explicit Entity() = default;

        ~Entity() {
            this->_components.clear();
        }

        /*!
         * @brief Add a Component to the Entity
         * @tparam T Component type
         * @tparam TArgs Component's constructor arguments
         * @param args Component's constructor arguments
         * @return The created Component
         */
        template<typename T, typename... TArgs> T *addComponent(TArgs&&... args);

        /*!
         * @brief Gets the first Component of the specified type
         * @tparam T The Component type
         * @return The Component
         */
        template<typename T> [[nodiscard]] T *getComponent() const;

        /*!
         * @brief Gets all Components of the specified type
         * @tparam T The Component type
         * @return The Components
         */
        template<typename T> [[nodiscard]] std::vector<T *> getComponents() const;

        /*!
         * @brief Check if the Entity contains all of the specified Components
         */
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
    T *Engine::Entity::addComponent(TArgs &&... args)
    {
        std::unique_ptr<Component> component = std::make_unique<T>(std::forward<TArgs>(args)...);

        component->setInfo(typeid(T).name());
        this->_components.push_back(std::move(component));
        return static_cast<T *>(this->_components.back().get());
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

    template<typename T>
    std::vector<T *> Engine::Entity::getComponents() const
    {
        std::vector<T *> res = {};

        for (auto &component : this->_components) {
            if (typeid(T).name() == component->getInfo())
                res.push_back(static_cast<T *>(component.get()));
        }
        return res;
    }

}
#endif //RTYPE_ENTITY_HPP