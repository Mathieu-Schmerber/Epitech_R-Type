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
        Point<int> _pos;
        double _rotation;
        Point<double> _normal;

    public:
        explicit TransformComponent(const Point<int> &pos = {0, 0},
                                    double rotation = 0,
                                    const Point<double> &normal = {1, 0})
                : _pos(pos), _rotation(rotation), _normal(normal), Component() {}

        Point<int> getPos() const { return this->_pos; }
        void setPos(const Point<int> &pos) {this->_pos = pos;}

        double getRotation() const {return this->_rotation;}
        void setRotation(double rotation) {this->_rotation = rotation;}

        Point<double> getNormal() const
        {
            return Geometry::rotateVector(this->_normal, this->_rotation);
        }

    };

}

#endif //RTYPE_TRANSFORMCOMPONENT_HPP