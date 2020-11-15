//
// Created by mathi on 06/11/2020.
//

#include "SocketParser.hpp"
#include "tools/AssetPool.hpp"
#include "components/NetworkComponent.hpp"
#include "components/SpriteComponent.hpp"
#include "components/TransformComponent.hpp"
#include "components/VelocityComponent.hpp"
#include "components/TextComponent.hpp"
#include "tools/Utils.hpp"

std::pair<std::vector<Engine::Inputs>, std::vector<Engine::Inputs>>
SocketParser::unparseUdpInputs(const std::vector<int> &in)
{
    std::vector<Engine::Inputs> pressed;
    std::vector<Engine::Inputs> released;

    if (in.at(0) == -1 || in.size() <= 3)
        return {{},
                {}};
    for (size_t i = 2; i < in.at(1) + 2; ++i)
        pressed.push_back(static_cast<Engine::Inputs>(in.at(i)));
    for (size_t i = 2 + pressed.size() + 1; i < in.at(2 + pressed.size()); i++)
        released.push_back(static_cast<Engine::Inputs>(in.at(i)));
    return {pressed, released};
}

std::vector<int> SocketParser::parseUdpEntity(const std::shared_ptr<Engine::Entity> &entity)
{
    if (entity->getComponent<Engine::SpriteComponent>())
        return parseUdpSprite(entity);
    return parseUdpText(entity);
}

std::vector<int> SocketParser::parseUdpText(const std::shared_ptr<Engine::Entity> &entity)
{
    std::vector<int> parsed;
    static auto pool = new Engine::AssetPool("../../client/assets");
    auto transform = entity->getComponent<Engine::TransformComponent>();
    auto text = entity->getComponent<Engine::TextComponent>();

    parsed.push_back(Text);
    parsed.push_back(entity->getComponent<Engine::NetworkComponent>()->getNetworkId());
    parsed.push_back(static_cast<int>(pool->getIndexFromPath(text->getText()->getFont()->getFileName())));
    parsed.push_back(static_cast<int>(pool->getIndexFromPath(text->getText()->toStdString())));
    parsed.push_back(static_cast<int>(text->getText()->getPosition().x));
    parsed.push_back(static_cast<int>(text->getText()->getPosition().y));
    parsed.push_back(static_cast<int>(transform->getRotation()));
    parsed.push_back(static_cast<int>(text->getText()->getCharacterSize()));
    parsed.push_back(static_cast<int>(text->getText()->getLetterSpacing()));
    parsed.push_back(static_cast<int>(text->getLayer()));
    parsed.push_back(static_cast<int>(text->getText()->getFillColor().alpha));

    return parsed;
}

std::vector<int> SocketParser::parseUdpSprite(const std::shared_ptr<Engine::Entity> &entity)
{
    std::vector<int> parsed;
    static auto pool = new Engine::AssetPool("../../client/assets");
    auto transform = entity->getComponent<Engine::TransformComponent>();
    auto sprite = entity->getComponent<Engine::SpriteComponent>();

    parsed.push_back(Sprite);
    parsed.push_back(entity->getComponent<Engine::NetworkComponent>()->getNetworkId());
    parsed.push_back(static_cast<int>(transform->getPos().x));
    parsed.push_back(static_cast<int>(transform->getPos().y));
    parsed.push_back(static_cast<int>(transform->getRotation()));
    parsed.push_back(static_cast<int>(pool->getIndexFromPath(sprite->getTexture()->getFilename())));
    parsed.push_back(static_cast<int>(sprite->getSprite()->getRect().x1));
    parsed.push_back(static_cast<int>(sprite->getSprite()->getRect().x2));
    parsed.push_back(static_cast<int>(sprite->getSprite()->getRect().y1));
    parsed.push_back(static_cast<int>(sprite->getSprite()->getRect().y2));
    parsed.push_back(static_cast<int>(sprite->getLayer()));
    return parsed;
}
