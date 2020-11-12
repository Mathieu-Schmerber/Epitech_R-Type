/*
** EPITECH PROJECT, 2020
** RType
** File description:
** Created by Cyprien
*/


#ifndef RTYPE_TEXTCOMPONENT_HPP
#define RTYPE_TEXTCOMPONENT_HPP

#include "ecs/Component.hpp"
#include "graphical/AText.hpp"

namespace Engine {

class TextComponent : public Engine::Component {
private:
    std::unique_ptr<Engine::AText> _text;
    std::shared_ptr<Engine::AFont> _font;
    bool _hasToBeDraw = true;
    int _layer;

public:
    explicit TextComponent() : _layer(0), _text(nullptr), Engine::Component() {}
    explicit TextComponent(int layer, std::unique_ptr<Engine::AText> text) : Engine::Component(), _layer(layer),
    _text(std::move(text)) {}

    [[nodiscard]] std::unique_ptr<Engine::AText> &getText() {return this->_text;}
    void setText(std::unique_ptr<Engine::AText> text) { this->_text = std::move(text);}
    void draw(std::shared_ptr<Engine::AWindow> &window, Engine::Point<float> position, float angle) {
        if (_hasToBeDraw)
            _text->draw(window, position, angle);
    }
    void setLayer(int layer) {this->_layer = layer;}
    [[nodiscard]] int getLayer() const {return this->_layer;}
};

}

#endif //RTYPE_TEXTCOMPONENT_HPP
