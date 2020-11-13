//
// Created by mathi on 13/11/2020.
//

#ifndef RTYPE_COLLECTIBLECOMPONENT_HPP
#define RTYPE_COLLECTIBLECOMPONENT_HPP

#include "ecs/Component.hpp"

class CollectibleComponent : public Engine::Component {

public:
    enum Type {SENTINEL, UPGRADE};

    explicit CollectibleComponent() : _bonusValue(0), _type(UPGRADE), Engine::Component() {}
    explicit CollectibleComponent(double bonusValue, Type type) : _bonusValue(bonusValue), _type(type), Engine::Component() {}

    [[nodiscard]] double getBonusValue() const {return _bonusValue;}
    void setBonusValue(double bonusValue) {_bonusValue = bonusValue;}

    [[nodiscard]] Type getType() const {return _type;}
    void setType(Type type) {_type = type;}

private:
    double _bonusValue;
    Type _type;
};

#endif //RTYPE_COLLECTIBLECOMPONENT_HPP
