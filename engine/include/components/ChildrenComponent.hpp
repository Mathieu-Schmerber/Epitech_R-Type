//
// Created by mathi on 01/11/2020.
//

#ifndef RTYPE_CHILDRENCOMPONENT_HPP
#define RTYPE_CHILDRENCOMPONENT_HPP

#include "ecs/Entity.hpp"

namespace Engine {

    class ChildrenComponent : Engine::Component {
    private:
        std::vector<std::shared_ptr<Entity>> _children;

    public:
        explicit ChildrenComponent() : Component() {}

        void addChild(std::shared_ptr<Entity> &child) {this->_children.emplace_back(child);}
        [[nodiscard]] std::vector<std::shared_ptr<Entity>> getChildren() const {return this->_children;}
    };
}

#endif //RTYPE_CHILDRENCOMPONENT_HPP