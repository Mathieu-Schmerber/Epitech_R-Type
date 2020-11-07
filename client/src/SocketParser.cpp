//
// Created by mathi on 06/11/2020.
//

#include "SocketParser.hpp"
#include "tools/Utils.hpp"
#include "sfml/SpriteSfml.hpp"
#include "components/NetworkComponent.hpp"
#include "components/SpriteComponent.hpp"
#include "components/TransformComponent.hpp"

std::vector<int> SocketParser::parseUdpInputs(int clientId, const std::vector<Engine::Inputs> &pressed, const std::vector<Engine::Inputs> &released)
{
    std::vector<int> parsed;

    parsed.push_back(clientId);
    parsed.push_back(static_cast<int>(pressed.size()));
    for (auto &i : pressed)
        parsed.push_back(static_cast<int>(i));
    parsed.push_back(static_cast<int>(released.size()));
    for (auto &i : released)
        parsed.push_back(static_cast<int>(i));
    return parsed;
}

std::shared_ptr<Engine::Entity> SocketParser::unparseUdpEntity(const std::vector<int> &in)
{
    auto entity = new Engine::Entity();
    Engine::SpriteComponent *sprite = nullptr;

    if (in.size() >= 9)
        return nullptr;
    entity->addComponent<Engine::NetworkComponent>(in.at(0));
    entity->addComponent<Engine::TransformComponent>(Engine::Point<int>{in.at(1), in.at(2)}, in.at(3));
    entity->addComponent<Engine::SpriteComponent>();
    sprite = entity->getComponent<Engine::SpriteComponent>();
    // TODO: set texture thanks to the index: in.at(4)
    auto spr = std::make_unique<SpriteSFML>("../../client/assets/images/starships/blue_starship_166x17_33x17.png");
    sprite->setDisplay(std::move(spr));
    // TODO: ^^^This is a temporary texture set ^^^
    sprite->getSprite()->setRect({in.at(5), in.at(6), in.at(7), in.at(8)});
    return std::shared_ptr<Engine::Entity>(entity);
}

void SocketParser::updateEntityFromUdp(std::shared_ptr<Engine::Entity> &entity, const std::vector<int> &in)
{
    auto *sprite = entity->getComponent<Engine::SpriteComponent>();

    if (in.size() >= 9)
        return;
    entity->getComponent<Engine::TransformComponent>()->setPos({in.at(1), in.at(2)});
    entity->getComponent<Engine::TransformComponent>()->setRotation(in.at(3));
    sprite->getSprite()->setRect({in.at(5), in.at(6), in.at(7), in.at(8)});
    // TODO: set texture thanks to the index: in.at(4)
}