//
// Created by paul on 11/6/20.
//

#ifndef RTYPE_LOBBYCARD_HPP
#define RTYPE_LOBBYCARD_HPP

#include "ecs/Entity.hpp"
#include "tools/Geometry.hpp"
#include "components/TransformComponent.hpp"
#include "components/SpriteComponent.hpp"
#include "components/ClickableComponent.hpp"
#include "components/TextComponent.hpp"

namespace Engine {

    class LobbyCard : public Engine::Entity {
        public:
        LobbyCard(const Point<int> &pos,
            std::unique_ptr<Engine::ASprite> background,
            std::shared_ptr<Engine::AFont> &font,
            void (*onClick)(std::shared_ptr<Engine::AScene> &),
            std::shared_ptr<Engine::AScene> arg,
            int layer = 1) : Engine::Entity()

        {
            this->addComponent<TransformComponent>(pos);
            this->addComponent<SpriteComponent>(layer, std::move(background));
            this->addComponent<ClickableComponent>(onClick, arg);

            for (int i = 0; i < 4; i++) {
                auto starship = std::make_unique<SpriteSFML>(EMPTY_STARSHIP_PATH);
                this->addComponent<SpriteComponent>(layer + 1, std::move(starship));
            }

            for (int i = 0; i < 3; i++) {
                auto text = std::make_unique<TextSFML>("Cyprien", font, 50);
                this->addComponent<TextComponent>(layer + 1, std::move(text));
            }
        }
    };

}

#endif //RTYPE_LOBBYCARD_HPP
