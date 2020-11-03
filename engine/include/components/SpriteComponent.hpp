//
// Created by mathi on 30/10/2020.
//

#ifndef RTYPE_SPRITECOMPONENT_HPP
#define RTYPE_SPRITECOMPONENT_HPP

#include "graphical/ASprite.hpp"
#include "ecs/Component.hpp"
#include <memory>

namespace Engine {

    class SpriteComponent : public Engine::Component {
    private:
        std::unique_ptr<Engine::ASprite> _sprite;
        int _layer;

    public:
        explicit SpriteComponent() : _layer(0), Engine::Component() {};
        explicit SpriteComponent(int layer, std::unique_ptr<Engine::ASprite> sprite) : _layer(layer), _sprite(std::move(sprite)), Engine::Component() {};

        std::unique_ptr<Engine::ASprite> &getSprite() {return this->_sprite;}
        void setDisplay(std::unique_ptr<Engine::ASprite> sprite) { this->_sprite = std::move(sprite);}
        void setLayer(int layer) {this->_layer = layer;}
        int getLayer() const {return this->_layer;}
    };
}

#endif //RTYPE_SPRITECOMPONENT_HPP
