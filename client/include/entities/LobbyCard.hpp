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
#include "components/ClickableComponent.hpp"
#include "components/ColliderComponent.hpp"
#include "components/TextComponent.hpp"
#include "components/LobbyComponent.hpp"
#include "scenes/SceneEnum.hpp"

class LobbyCard : public Engine::Entity {
    public:
    LobbyCard(const Engine::Point<int> &pos,
        LobbyComponent &lobby,
        std::shared_ptr<Engine::AFont> &font,
        int layer = 1) : Engine::Entity()

    {
        auto background = std::make_unique<SpriteSFML>(LOBBY_CARD_PATH);
        float relativeStarshipPositionX = 40.0;
        this->addComponent<Engine::TransformComponent>(pos);
        this->addComponent<Engine::SpriteComponent>(layer, std::move(background));
        this->addComponent<Engine::ClickableComponent>();
        this->addComponent<Engine::ColliderComponent>(0, Engine::Box<double>{{(double)pos.x, (double)pos.y}, {850.0, 150.0}});
        std::shared_ptr<Engine::ATexture> starshipTexture = std::make_shared<TextureSFML>(ALL_STARSHIP_PATH);
        std::shared_ptr<Engine::ATexture> emptyStarshipTexture = std::make_shared<TextureSFML>(EMPTY_STARSHIP_PATH);
        
        for (int i = 0; i < lobby.getNbActualClient(); i++) {
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
        }
    }
};

#endif //RTYPE_LOBBYCARD_HPP
