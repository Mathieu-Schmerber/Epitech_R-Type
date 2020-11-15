/*!
 * @file PlayerAndStarshipEntity.hpp
 * @brief PlayerAndStarshipEntity prototypes
 * @authors Paul.S
 * @version 1.0
 * @date 14/11/2020
 *
*/

#ifndef RTYPE_PLAYERANDSTARSHIPENTITY_HPP
#define RTYPE_PLAYERANDSTARSHIPENTITY_HPP

#include <components/PlayerAndStarshipComponent.hpp>
#include "ecs/Entity.hpp"
#include "tools/Geometry.hpp"
#include "components/TransformComponent.hpp"
#include "components/SpriteComponent.hpp"
#include "sfml/TextSFML.hpp"
#include "sfml/SpriteSfml.hpp"
#include "components/ClickableComponent.hpp"
#include "components/ColliderComponent.hpp"
#include "components/TextComponent.hpp"
#include "components/LobbyComponent.hpp"
#include "scenes/SceneEnum.hpp"

class PlayerAndStarshipEntity : public Engine::Entity {
    public:
    /*!
     * \brief PlayerAndStarshipEntity constructor
     * \param playerName player's text set by default to "player X"
     *
     * Generate a text and a starship sprite to the screen.
    */
    explicit PlayerAndStarshipEntity(const std::string &playerName) : Engine::Entity() {
        std::shared_ptr<Engine::ATexture> starshipTexture = std::make_shared<TextureSFML>(ALL_STARSHIP_PATH);
        std::shared_ptr<Engine::AFont> font = std::make_shared<FontSFML>(PIXEBOY_FONT_PATH);

        this->addComponent<PlayerAndStarshipComponent>();
        this->addComponent<Engine::TransformComponent>();
        auto starship = std::make_unique<SpriteSFML>(starshipTexture);
        starship->setScale({static_cast<double>(STARSHIP_SCALE_X), static_cast<double>(STARSHIP_SCALE_Y)});
        starship->setRect({Engine::Box<double>({STARSHIP_WIDTH * 4, 0}, {STARSHIP_WIDTH, STARSHIP_HEIGHT})});
        starship->setOrigin(Engine::Point<double>{-200, 0});
        this->addComponent<Engine::SpriteComponent>(2, std::move(starship));

        auto playerNameText = std::make_unique<TextSFML>(playerName, font, 80);
        playerNameText->setOrigin(Engine::Point<double>{0, 40.0});
        this->addComponent<Engine::TextComponent>(2, std::move(playerNameText));
    }
};

#endif //RTYPE_PLAYERANDSTARSHIPENTITY_HPP
