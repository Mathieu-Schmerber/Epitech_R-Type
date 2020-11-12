//
// Created by mathi on 30/10/2020.
//

#ifndef RTYPE_TRANSFORMCOMPONENT_HPP
#define RTYPE_TRANSFORMCOMPONENT_HPP

#include <utility>
#include <cmath>
#include "tools/Geometry.hpp"
#include "ecs/Component.hpp"

namespace Engine {

    class TransformComponent : public Engine::Component {
    private:
        Point<float> _pos;
        float _rotation;
        Point<float> _normal;

    public:
        explicit TransformComponent(const Point<float> &pos = {0.0, 0.0},
                                    float rotation = 0,
                                    const Point<float> &normal = {1, 0})
                : _pos(pos), _rotation(rotation), _normal(normal), Component() {}

        [[nodiscard]] Point<float> getPos() const { return this->_pos; }
        void setPos(const Point<float> &pos) {this->_pos = pos;}
        void movePos(const Vector<float> &increment) {
            this->_pos.x += increment.x;
            this->_pos.y += increment.y;
        }

        [[nodiscard]] float getRotation() const {return this->_rotation;}
        void setRotation(float rotation) {this->_rotation = rotation;}

        [[nodiscard]] Point<float> getNormal() const
        {
            return Geometry::rotateVector(this->_normal, this->_rotation);
        }

    };

}

#endif //RTYPE_TRANSFORMCOMPONENT_HPP