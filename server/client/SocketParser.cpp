//
// Created by mathi on 06/11/2020.
//

#include "SocketParser.hpp"
#include "tools/AssetPool.hpp"
#include "components/NetworkComponent.hpp"
#include "components/SpriteComponent.hpp"
#include "components/TransformComponent.hpp"
#include "components/VelocityComponent.hpp"

std::pair<std::vector<Engine::Inputs>, std::vector<Engine::Inputs>> SocketParser::unparseUdpInputs(const std::vector<int> &in)
{
    std::vector<Engine::Inputs> pressed;
    std::vector<Engine::Inputs> released;

    if (in.at(0) == -1 || in.size() <= 3)
        return {{}, {}};
    for (size_t i = 2; i < in.at(1) + 2; ++i)
        pressed.push_back(static_cast<Engine::Inputs>(in.at(i)));
    for (size_t i = 2 + pressed.size() + 1; i < in.at(2 + pressed.size()); i++)
        released.push_back(static_cast<Engine::Inputs>(in.at(i)));
    return {pressed, released};
}

std::vector<int> SocketParser::parseUdpEntity(const std::shared_ptr<Engine::Entity>& entity)
{
    static auto pool = new Engine::AssetPool("../../client/assets");
    std::vector<int> parsed;
    auto transform = entity->getComponent<Engine::TransformComponent>();
    auto sprite = entity->getComponent<Engine::SpriteComponent>();

    parsed.push_back(entity->getComponent<Engine::NetworkComponent>()->getNetworkId());
    parsed.push_back(transform->getPos().x);
    parsed.push_back(transform->getPos().y);
    parsed.push_back(static_cast<int>(transform->getRotation()));
    parsed.push_back(static_cast<int>(pool->getIndexFromPath(sprite->getTexture()->getFilename())));
    parsed.push_back(sprite->getSprite()->getRect().x1);
    parsed.push_back(sprite->getSprite()->getRect().x2);
    parsed.push_back(sprite->getSprite()->getRect().y1);
    parsed.push_back(sprite->getSprite()->getRect().y2);
    parsed.push_back(sprite->getLayer());
    return parsed;
}