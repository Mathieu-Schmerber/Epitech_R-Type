//
// Created by mathi on 06/11/2020.
//

#include "SocketParser.hpp"
#include "components/NetworkComponent.hpp"
#include "components/SpriteComponent.hpp"
#include "components/TransformComponent.hpp"

std::pair<std::vector<Engine::Inputs>, std::vector<Engine::Inputs>> SocketParser::unparseUdpInputs(const std::vector<int> &in)
{
    size_t i;
    std::vector<Engine::Inputs> pressed;
    std::vector<Engine::Inputs> released;

    for (i = 2; i < in.at(1); ++i)
        pressed.push_back(static_cast<Engine::Inputs>(in.at(i)));
    i++;
    for (size_t j = 0; j < in.at(i); ++j)
        pressed.push_back(static_cast<Engine::Inputs>(in.at(i + j)));
    return {pressed, released};
}

std::vector<int> SocketParser::parseUdpEntity(const std::shared_ptr<Engine::Entity> &entity)
{
    std::vector<int> parsed;
    auto transform = entity->getComponent<Engine::TransformComponent>();
    auto sprite = entity->getComponent<Engine::SpriteComponent>();

    parsed.push_back(entity->getComponent<Engine::NetworkComponent>()->getNetworkId());
    parsed.push_back(transform->getPos().x);
    parsed.push_back(transform->getPos().y);
    parsed.push_back(transform->getRotation());
    //TODO: push a texture index <here>
    parsed.push_back(sprite->getSprite()->getRect().x1);
    parsed.push_back(sprite->getSprite()->getRect().y1);
    parsed.push_back(sprite->getSprite()->getRect().x2);
    parsed.push_back(sprite->getSprite()->getRect().y2);
    return parsed;
}