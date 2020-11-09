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
    LobbyCard(short port, int lobbyId, int maxPlayers, int idClientMaster) : Engine::Entity()
    {
        std::shared_ptr<Engine::ATexture> starshipTexture = std::make_shared<TextureSFML>(ALL_STARSHIP_PATH);
        auto background = std::make_unique<SpriteSFML>(LOBBY_CARD_PATH);
        float relativeStarshipPositionX = 40.0;

        this->addComponent<Engine::TransformComponent>();
        this->addComponent<Engine::SpriteComponent>(1, std::move(background));
        this->addComponent<Engine::ClickableComponent>();
        this->addComponent<Engine::ColliderComponent>(0, Engine::Box<double>{{0, 0}, {850.0, 150.0}});
        this->addComponent<LobbyComponent>(port, lobbyId, maxPlayers, 0, idClientMaster);
        for (int i = 0; i < maxPlayers; ++i) {
            auto starship = std::make_unique<SpriteSFML>(starshipTexture);
            starship->setScale({static_cast<float>(STARSHIP_SCALE_X), static_cast<float>(STARSHIP_SCALE_Y)});
            starship->setRect({Engine::Box<int>({STARSHIP_WIDTH * 4, 0}, {STARSHIP_WIDTH, STARSHIP_HEIGHT})});
            starship->setOrigin(Engine::Point<float>{static_cast<float>(-relativeStarshipPositionX), -28.0});
            relativeStarshipPositionX += 50.0;
            this->addComponent<Engine::SpriteComponent>(2, std::move(starship));
        }
        /*for (int i = 0; i < lobby.getNbActualClient(); i++) {
            auto starship = std::make_unique<SpriteSFML>(starshipTexture);
            starship->setScale({static_cast<float>(STARSHIP_SCALE_X), static_cast<float>(STARSHIP_SCALE_Y)});
            starship->setRect({Engine::Box<int>({STARSHIP_WIDTH * i, 0}, {STARSHIP_WIDTH, STARSHIP_HEIGHT})});
            starship->setOrigin(Engine::Point<float>{static_cast<float>(-relativeStarshipPositionX), -28.0});
            relativeStarshipPositionX += 50.0;
            this->addComponent<Engine::SpriteComponent>(layer + 1, std::move(starship));
        }
        for (int i =  lobby.getNbActualClient(); i < lobby.getNbMaxClient(); i++) {
            auto starship = std::make_unique<SpriteSFML>(emptyStarshipTexture);
            starship->setScale({static_cast<float>(STARSHIP_SCALE_X), static_cast<float>(STARSHIP_SCALE_Y)});
            starship->setOrigin(Engine::Point<float>{static_cast<float>(-relativeStarshipPositionX), -28.0});
            relativeStarshipPositionX += 50.0;
            this->addComponent<Engine::SpriteComponent>(layer + 1, std::move(starship));
        }
        for (int i = 0; i < 3; i++) {
            auto text = std::make_unique<TextSFML>("None",font, 40);
            if (i == 0) {
                text->setString(std::to_string(lobby.getLobbyId()));
                text->setOrigin(Engine::Point<float>{-175, 0});
            } else if (i == 1) {
                text->setString(std::to_string(lobby.getPort()));
                text->setOrigin(Engine::Point<float>{-380, 0});
            } else {
                text->setString(std::to_string(lobby.getNbActualClient()) + " / " + std::to_string(lobby.getNbMaxClient()));
                text->setOrigin(Engine::Point<float>{-715, 0});
            }
            this->addComponent<Engine::TextComponent>(layer + 1, std::move(text));
        }*/
    }
};

#endif //RTYPE_LOBBYCARD_HPP
