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
        std::shared_ptr<Engine::ATexture> _texture;
        bool _hasToBeDraw = true;
        int _layer;

    public:
        explicit SpriteComponent() : _layer(0), Engine::Component() {};
        explicit SpriteComponent(int layer, std::unique_ptr<Engine::ASprite> sprite) : _layer(layer),
        _sprite(std::move(sprite)), _texture(_sprite->getTexture()), Engine::Component() {};

        [[nodiscard]] std::unique_ptr<Engine::ASprite> &getSprite() {return this->_sprite;}
        [[nodiscard]] std::shared_ptr<Engine::ATexture> &getTexture() {return this->_texture;}
        [[nodiscard]] bool isVisible() const {return this->_hasToBeDraw;}
        void setDisplay(std::unique_ptr<Engine::ASprite> sprite) { this->_sprite = std::move(sprite);}
        void hasToBeDraw(bool draw) {_hasToBeDraw = draw;};
        [[nodiscard]] bool getHasToBeDraw() const {return _hasToBeDraw;};
        void draw(std::shared_ptr<Engine::AWindow> &window, Engine::Point<double> position, double angle) {
            if (_hasToBeDraw)
                _sprite->draw(window, position, angle);
        }
        void setLayer(int layer) {this->_layer = layer;}
        [[nodiscard]] int getLayer() const {return this->_layer;}
    };
}

#endif //RTYPE_SPRITECOMPONENT_HPP
