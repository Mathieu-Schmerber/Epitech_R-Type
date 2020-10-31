//
// Created by mathi on 30/10/2020.
//

#ifndef RTYPE_TRANSFORMCOMPONENT_HPP
#define RTYPE_TRANSFORMCOMPONENT_HPP

#include <utility>
#include <math.h>
#include "ecs/Component.hpp"

class TransformComponent : public Engine::Component {
private:
    std::pair<int, int> _pos;
    double _rotation;
    std::pair<double, double> _normal;

public:
    explicit TransformComponent(const std::pair<int, int> &pos = {0, 0},
                                double rotation = 0,
                                const std::pair<double, double> &normal = {0, 1});

    std::pair<int, int> getPos() const;
    void setPos(const std::pair<int, int> &pos);

    double getRotation() const;
    void setRotation(double rotation);

    std::pair<double, double> getNormal() const;

};

#endif //RTYPE_TRANSFORMCOMPONENT_HPP
