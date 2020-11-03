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

class SpriteSFML : public Engine::ASprite {
public:
    SpriteSFML() = default;
    explicit SpriteSFML(const std::string& filename) : Engine::ASprite() {
        loadFromFile(filename);
    }

    void loadFromFile(std::string filename);

    void setPosition(Engine::Point<float> position);
    Engine::Point<float> getPosition() const;
    void setRotation(float angle);
    float getRotation();
    void setOrigin(Engine::Point<float> origin) override;
    Engine::Point<float> getOrigin() const;
    void setScale(Engine::Scale<float> scale) override;
    Engine::Scale<float> getScale() const;
    void setRect(Engine::Box<int> rect) override;
    Engine::Box<int> getRect() const override;

    Engine::Size<int> getSize() override;

    void draw(std::shared_ptr<Engine::AWindow> &window, Engine::Point<int> position, float angle) override;

private:
    sf::Sprite _sprite;
    sf::Texture _texture;
};


#endif //RTYPE_SPRITESFML_HPP
