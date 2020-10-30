//
// Created by mathi on 30/10/2020.
//

#include "TransformComponent.hpp"

TransformComponent::TransformComponent(const std::pair<int, int> &pos, double rotation, const std::pair<double, double> &normal)
: _pos(pos), _rotation(rotation), _normal(normal), Component() {}

std::pair<int, int> TransformComponent::getPos() const { return _pos; }
void TransformComponent::setPos(const std::pair<int, int> &pos) {_pos = pos;}

double TransformComponent::getRotation() const {return _rotation;}
void TransformComponent::setRotation(double rotation) {_rotation = rotation;}

std::pair<double, double> TransformComponent::getNormal() const
{
    const double PI = 3.141592653589793238463;
    double angle = this->_rotation * (PI / 180);
    std::pair<double, double> res = {
            _normal.first * cos(angle) - _normal.second * sin(angle),
            _normal.first * sin(angle) + _normal.second * cos(angle)
    };

    return res;
}