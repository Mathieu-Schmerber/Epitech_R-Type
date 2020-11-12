//
// Created by mathi on 07/11/2020.
//

#ifndef RTYPE_PLAYER_HPP
#define RTYPE_PLAYER_HPP

#include "ecs/Entity.hpp"
#include "dataHolders/DataSprite.hpp"
#include "components/SpriteComponent.hpp"
#include "components/TransformComponent.hpp"
#include "components/AnimationComponent.hpp"
#include "components/VelocityComponent.hpp"
#include "components/ControllerComponent.hpp"
#include "components/ColliderComponent.hpp"
#include "components/ManualWeaponComponent.hpp"

class Player : public Engine::Entity
{
private:
    const Engine::Size<float> _size = {33, 17};
    const std::vector<std::string> ships = {
            "../../client/assets/images/starships/blue_starship_166x17_33x17.png",
            "../../client/assets/images/starships/green_starship_166x17_33x17.png",
            "../../client/assets/images/starships/red_starship_166x17_33x17.png",
            "../../client/assets/images/starships/yellow_starship_166x17_33x17.png"
    };
public:
    enum PlayerState {IDLE = 0, DOWN = 1, UP = 2};

    explicit Player(char playerNumber, const Engine::Point<float> &pos = {0.0, 0.0}) : Engine::Entity()
    {
        auto spr = std::make_unique<DataSprite>(ships[playerNumber], Engine::Box<float>{{0, 0}, _size});

        this->addComponent<Engine::TransformComponent>(pos);
        this->addComponent<Engine::VelocityComponent>();
        this->addComponent<Engine::SpriteComponent>(1, std::move(spr));
        this->addComponent<Engine::ControllerComponent>();
        this->addComponent<Engine::ColliderComponent>();
        this->addComponent<Engine::AnimationComponent>(0.2, std::map<int, std::vector<Engine::Box<float>>>{
                {IDLE, {
                            {_size.x * 2, _size.x * 3, 0, _size.y}}},
                {DOWN, {
                            {_size.x * 2, _size.x * 3, 0, _size.y},
                            {_size.x * 1, _size.x * 2, 0, _size.y},
                            {_size.x * 0, _size.x * 1, 0, _size.y}}},
                {UP, {
                            {_size.x * 2, _size.x * 3, 0, _size.y},
                            {_size.x * 3, _size.x * 4, 0, _size.y},
                            {_size.x * 4, _size.x * 5, 0, _size.y}}}

        });
        this->getComponent<Engine::AnimationComponent>()->setAnimation(IDLE, false);
        this->addComponent<ManualWeaponComponent>(1, 0.5, 0.2);
    }

};


#endif //RTYPE_PLAYER_HPP
