//
// Created by mathi on 12/11/2020.
//

#ifndef RTYPE_GROUND_HPP
#define RTYPE_GROUND_HPP

#include "tools/Geometry.hpp"
#include "components/TransformComponent.hpp"
#include "components/SpriteComponent.hpp"
#include "components/ParallaxComponent.hpp"
#include "components/VelocityComponent.hpp"
#include "components/ColliderComponent.hpp"
#include "dataHolders/DataSprite.hpp"
#include "ecs/Entity.hpp"

#define GROUND_WIDTH 235
#define GROUND_HEIGHT 71

class Ground : public Engine::Entity
{
private:
    Engine::Size<int> _size = {GROUND_WIDTH, GROUND_HEIGHT};

public:
    explicit Ground(const Engine::Point<int> &pos, const Engine::Point<int> &limit, const Engine::Vector<double> &speed) : Engine::Entity()
    {
        auto spr = std::make_unique<DataSprite>("../../client/assets/images/platform/bottom_platform_single.png");

        spr->setRect({{0, 0}, _size});
        this->addComponent<Engine::TransformComponent>(pos);
        this->addComponent<Engine::ParallaxComponent>(pos, limit);
        this->addComponent<Engine::VelocityComponent>(speed);
        this->addComponent<Engine::ColliderComponent>(0, pos, _size);
        this->addComponent<Engine::SpriteComponent>(1, std::move(spr));
    }
};

#endif //RTYPE_GROUND_HPP
