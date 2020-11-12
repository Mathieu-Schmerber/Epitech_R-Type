//
// Created by paul on 11/6/20.
//

#ifndef RTYPE_LOBBYCARD_HPP
#define RTYPE_LOBBYCARD_HPP

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

class LobbyCard : public Engine::Entity {
    public:
    LobbyCard(short port, int lobbyId, int maxPlayers, int idClientMaster) : Engine::Entity() {
        std::shared_ptr<Engine::ATexture> starshipTexture = std::make_shared<TextureSFML>(ALL_STARSHIP_PATH);
        std::shared_ptr<Engine::AFont> font = std::make_shared<FontSFML>(PIXEBOY_FONT_PATH);
        auto background = std::make_unique<SpriteSFML>(LOBBY_CARD_PATH);
        float relativeStarshipPositionX = 40.0;

        this->addComponent<Engine::TransformComponent>();
        this->addComponent<Engine::SpriteComponent>(1, std::move(background));
        this->addComponent<Engine::ClickableComponent>();
        this->addComponent<Engine::ColliderComponent>(0, Engine::Box<float>{{0,0},{850.0, 150.0}});
        this->addComponent<LobbyComponent>(port, lobbyId, maxPlayers, 0, idClientMaster);
        for (int i = 0; i < maxPlayers; ++i) {
            auto starship = std::make_unique<SpriteSFML>(starshipTexture);
            starship->setScale({static_cast<float>(STARSHIP_SCALE_X), static_cast<float>(STARSHIP_SCALE_Y)});
            starship->setRect({Engine::Box<float>({STARSHIP_WIDTH * 4, 0}, {STARSHIP_WIDTH, STARSHIP_HEIGHT})});
            starship->setOrigin(Engine::Point<float>{static_cast<float>(-relativeStarshipPositionX), -28.0});
            relativeStarshipPositionX += 50.0;
            this->addComponent<Engine::SpriteComponent>(2, std::move(starship));
        }
        auto idTxt = std::make_unique<TextSFML>(std::to_string(lobbyId), font, 40);
        auto portTxt = std::make_unique<TextSFML>(std::to_string(port), font, 40);
        auto playingTxt = std::make_unique<TextSFML>(std::to_string(lobbyId), font, 40);
        idTxt->setOrigin(Engine::Point<float>{-175, 0});
        portTxt->setOrigin(Engine::Point<float>{-380, 0});
        playingTxt->setOrigin(Engine::Point<float>{-715, 0});
        this->addComponent<Engine::TextComponent>(2, std::move(idTxt));
        this->addComponent<Engine::TextComponent>(2, std::move(portTxt));
        this->addComponent<Engine::TextComponent>(2, std::move(playingTxt));
    }
};

#endif //RTYPE_LOBBYCARD_HPP
