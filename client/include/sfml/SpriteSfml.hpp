/*
** EPITECH PROJECT, 2020
** RType
** File description:
** Created by Cyprien
*/


#ifndef RTYPE_SPRITESFML_HPP
#define RTYPE_SPRITESFML_HPP

#include <string>
#include <SFML/Graphics/Sprite.hpp>
#include <SFML/Graphics/Texture.hpp>
#include <SFML/Graphics/Sprite.hpp>
#include <SFML/Graphics/Transformable.hpp>
#include "tools/Geometry.hpp"
#include "graphical/ASprite.hpp"
#include "sfml/TextureSFML.hpp"

class SpriteSFML : public Engine::ASprite {
public:
    SpriteSFML() = default;
    explicit SpriteSFML(std::shared_ptr<Engine::ATexture> &texture) : Engine::ASprite() {
        setTexture(texture);
    }
    explicit SpriteSFML(const std::string &fileName) : Engine::ASprite() {
        _texture = std::make_shared<TextureSFML>(fileName);
        setTexture(_texture);
    }

    void setTexture(std::shared_ptr<Engine::ATexture> &texture) final;
    void setPosition(Engine::Point<float> position);
    [[nodiscard]] Engine::Point<float> getPosition() const override;
    void setRotation(float angle);
    [[nodiscard]] float getRotation();
    void setOrigin(Engine::Point<float> origin) override;
    [[nodiscard]] Engine::Point<float> getOrigin() const override;
    void setScale(Engine::Scale<float> scale) override;
    [[nodiscard]] Engine::Scale<float> getScale() const;
    void setRect(Engine::Box<int> rect) override;
    [[nodiscard]] Engine::Box<int> getRect() const override;
    [[nodiscard]] Engine::Size<int> getSize() const override;

    void draw(std::shared_ptr<Engine::AWindow> &window, Engine::Point<int> position, float angle) override;

private:
    sf::Sprite _sprite;
};


#endif //RTYPE_SPRITESFML_HPP
