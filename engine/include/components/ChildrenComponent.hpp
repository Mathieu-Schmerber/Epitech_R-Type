//
// Created by mathi on 01/11/2020.
//

#ifndef RTYPE_CHILDRENCOMPONENT_HPP
#define RTYPE_CHILDRENCOMPONENT_HPP

#include "tools/Utils.hpp"
#include "ecs/Entity.hpp"
#include "components/TransformComponent.hpp"

namespace Engine {

    class ChildrenComponent : public Engine::Component {
    private:
        std::vector<std::shared_ptr<Entity>> _children;

    public:
        explicit ChildrenComponent() : Component() {}

        void addChild(std::shared_ptr<Entity> &child) {
            if (child->getComponent<TransformComponent>())
                this->_children.emplace_back(child);
        }
        void removeChildIfExists(std::shared_ptr<Entity> &child)
        {
            if (Utils::isInVector(this->_children, child))
                Utils::removeFromVector(this->_children, child);
        }
        [[nodiscard]] std::vector<std::shared_ptr<Entity>> getChildren() const {return this->_children;}
    };
}

#endif //RTYPE_CHILDRENCOMPONENT_HPP