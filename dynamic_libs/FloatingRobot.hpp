/*
** EPITECH PROJECT, 2020
** RType
** File description:
** Created by Cyprien
*/


#ifndef RTYPE_FLOATINGROBOT_HPP
#define RTYPE_FLOATINGROBOT_HPP

#include "entities/Enemy.hpp"

#include <iostream>
#include <utility>
#include "components/AutomaticWeaponComponent.hpp"
#include "components/PatternComponent.hpp"

#define PATH "../../client/assets/images/enemies/ennemy_5_99x33_33x33.png"
#define SIZE_X 33
#define SIZE_Y 33

class FloatingRobot : public Enemy {
private:
    const Engine::Size<float> _size = {SIZE_X, SIZE_Y};

public:
    explicit FloatingRobot(const Engine::Point<float> &pos = {0, 0}) : Enemy(std::move(std::make_unique<DataSprite>(PATH, Engine::Box<float>{pos, {SIZE_X, SIZE_Y}})), pos) {
        this->addComponent<PatternComponent>();
        this->addComponent<AutomaticWeaponComponent>(1, 0.5, 0.2);  // FIXME changer les stats
        this->addComponent<Engine::AnimationComponent>(0.2, std::map<int, std::vector<Engine::Box<float>>>{
                {DEFAULT, {
                    {_size.x * 0, _size.x * 1, 0, _size.y},
                    {_size.x * 1, _size.x * 2, 0, _size.y},
                    {_size.x * 2, _size.x * 3, 0, _size.y}}}
        }, true);
    }
};

#endif //RTYPE_FLOATINGROBOT_HPP
