//
// Created by mathi on 02/11/2020.
//

#ifndef RTYPE_PARALLAXSLIDE_HPP
#define RTYPE_PARALLAXSLIDE_HPP

#include "ecs/Entity.hpp"
#include "components/VelocityComponent.hpp"
#include "components/ParallaxComponent.hpp"
#include "components/TransformComponent.hpp"
#include "components/SpriteComponent.hpp"
#include "tools/Geometry.hpp"

namespace Engine {

    class ParallaxSlide : public Engine::Entity {
    public:
        ParallaxSlide(const Point<int> &pos, const Point<int> &limit, const Vector<double> &speed, std::unique_ptr<ASprite> sprite)
        : Engine::Entity() {
            this->addComponent<TransformComponent>(pos);
            this->addComponent<SpriteComponent>(std::move(sprite));
            this->addComponent<ParallaxComponent>(pos, limit);
            this->addComponent<VelocityComponent>(speed);
        }
    };

}

#endif //RTYPE_PARALLAXSLIDE_HPP
