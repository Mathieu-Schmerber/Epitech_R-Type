/*!
 * @file SpriteSfml.hpp
 * @brief Manage SFML's sprite
 * @authors Cyprien.R
 * @version 1.0
 * @date 14/11/2020
 *
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
    /*!
    * \brief Sprite SFML default constructor
    *
   */
    SpriteSFML() = default;
    /*!
     * \brief Sprite SFML constructor with texture
     * \param texture a texture as shared_ptr which can be used to set the sprite's texture
     *
     * Create a sprite depending on an existing texture
    */
    explicit SpriteSFML(std::shared_ptr<Engine::ATexture> &texture) : Engine::ASprite() {
        setTexture(texture);
    }
    /*!
    * \brief Sprite SFML constructor with filename
    * \param fileName filename which be used to find, create and set the sprite's texture
    *
    * Create a sprite depending on an file (de facto, a texture will be created first)
   */
    explicit SpriteSFML(const std::string &fileName) : Engine::ASprite() {
        _texture = std::make_shared<TextureSFML>(fileName);
        setTexture(_texture);
    }

    void setTexture(std::shared_ptr<Engine::ATexture> &texture) final;
    void setPosition(Engine::Point<double> position);
    [[nodiscard]] Engine::Point<double> getPosition() const override;
    void setRotation(double angle);
    [[nodiscard]] double getRotation();
    void setOrigin(Engine::Point<double> origin) override;
    [[nodiscard]] Engine::Point<double> getOrigin() const override;
    void setScale(Engine::Scale<double> scale) override;
    [[nodiscard]] Engine::Scale<double> getScale() const;
    void setRect(Engine::Box<double> rect) override;
    [[nodiscard]] Engine::Box<double> getRect() const override;
    [[nodiscard]] Engine::Size<double> getSize() const override;

    void draw(std::shared_ptr<Engine::AWindow> &window, Engine::Point<double> position, double angle) override;

private:
    sf::Sprite _sprite;
};


#endif //RTYPE_SPRITESFML_HPP
