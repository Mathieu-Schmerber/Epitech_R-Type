//
// Created by paul on 11/10/20.
//

#ifndef RTYPE_CREATELOBBYENTITY_HPP
#define RTYPE_CREATELOBBYENTITY_HPP

#include "ecs/Entity.hpp"
#include "tools/Geometry.hpp"
#include "components/TransformComponent.hpp"
#include "components/SpriteComponent.hpp"
#include "sfml/TextSFML.hpp"
#include "sfml/SpriteSfml.hpp"
#include "components/ClickableComponent.hpp"
#include "components/ColliderComponent.hpp"
#include "components/TextComponent.hpp"
#include "components/CreateLobbyComponent.hpp"
#include "scenes/SceneEnum.hpp"

class CreateLobbyEntity : public Engine::Entity {
    public:
    explicit CreateLobbyEntity() : Engine::Entity() {
        std::shared_ptr<Engine::AFont> font = std::make_shared<FontSFML>(PIXEBOY_FONT_PATH);

        this->addComponent<Engine::TransformComponent>();
        this->addComponent<Engine::ClickableComponent>();
        this->addComponent<CreateLobbyComponent>();
        auto nbMaxOfClientsText = std::make_unique<TextSFML>("Number of players : 1", font, 100);
        nbMaxOfClientsText->setOrigin(Engine::Point<float>{0, 0});
        this->addComponent<Engine::TextComponent>(2, std::move(nbMaxOfClientsText));
    }
};

#endif //RTYPE_CREATELOBBYENTITY_HPP
