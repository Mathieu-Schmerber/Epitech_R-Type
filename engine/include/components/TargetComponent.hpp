/*
** EPITECH PROJECT, 2020
** RType
** File description:
** Created by Cyprien
*/


#ifndef RTYPE_TARGETCOMPONENT_HPP
#define RTYPE_TARGETCOMPONENT_HPP

#include "ecs/Component.hpp"
#include "ecs/Entity.hpp"
#include "tools/Utils.hpp"
#include "tools/RandomETU.hpp"

namespace Engine {

    /*!
     * @brief This component stores all the data needed to get track of a list of entity
     */
    class TargetComponent : public Engine::Component {
    private:
        std::vector<std::shared_ptr<Engine::Entity>> _targets{};

    public:
        explicit TargetComponent() = default;

        explicit TargetComponent(std::shared_ptr<Engine::Entity> target)
        { addTarget(target); }

        explicit TargetComponent(std::vector<std::shared_ptr<Engine::Entity>> &targets) : _targets(targets)
        {}

        void addTarget(std::shared_ptr<Engine::Entity> &target)
        {
            _targets.push_back(target);
        }

        void addTargets(std::vector<std::shared_ptr<Engine::Entity>> targets)
        {
            _targets += targets;
        }

        void removeTargetIfExists(std::shared_ptr<Entity> &target)
        {
            if (Utils::isInVector(this->_targets, target)) {
                Utils::removeFromVector(this->_targets, target);
            }
        }

        std::vector<std::shared_ptr<Engine::Entity>> getTargets() {
            return _targets;
        }

        [[nodiscard]] bool hasTargets() {
            return !_targets.empty();
        }

        std::shared_ptr<Engine::Entity> getRandomTarget() {
            return _targets.at(Engine::RandomETU::randETU(static_cast<int>(_targets.size()) - 1));
        }
    };
}

#endif //RTYPE_TARGETCOMPONENT_HPP
