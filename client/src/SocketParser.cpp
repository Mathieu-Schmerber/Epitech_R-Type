//
// Created by mathi on 06/11/2020.
//

#include "SocketParser.hpp"
#include "entities/LobbyCard.hpp"
#include "components/NetworkComponent.hpp"

SocketParser::SocketParser()
{
    this->_pool = std::make_unique<Engine::AssetPool>("../../client/assets");
}

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

    if (in.size() < 9)
        return nullptr;
    entity->addComponent<Engine::NetworkComponent>(in.at(0));
    entity->addComponent<Engine::TransformComponent>(Engine::Point<int>{in.at(1), in.at(2)}, in.at(3));
    entity->addComponent<Engine::SpriteComponent>();
    sprite = entity->getComponent<Engine::SpriteComponent>();
    auto spr = std::make_unique<SpriteSFML>(this->_pool->getPathFromIndex(in.at(4)));
    sprite->setDisplay(std::move(spr));
    sprite->getSprite()->setRect({in.at(5), in.at(6), in.at(7), in.at(8)});
    return std::shared_ptr<Engine::Entity>(entity);
}

void SocketParser::updateEntityFromUdp(std::shared_ptr<Engine::Entity> &entity, const std::vector<int> &in)
{
    auto *sprite = entity->getComponent<Engine::SpriteComponent>();
    auto inititalPos = entity->getComponent<Engine::TransformComponent>()->getPos();
    auto smooth = Engine::Point<int>{(inititalPos.x + in.at(1)) / 2, (inititalPos.y + in.at(2)) / 2};

    if (in.size() < 9)
        return;
    entity->getComponent<Engine::TransformComponent>()->setPos(smooth);
    entity->getComponent<Engine::TransformComponent>()->setRotation(in.at(3));
    sprite->getSprite()->setRect({in.at(5), in.at(6), in.at(7), in.at(8)});
}

std::shared_ptr<Engine::Entity> SocketParser::unparseTcpLobby(const std::vector<int> &in)
{
    //TODO: TMP RAW DATA (Get it from the "in")
    int lobbyId = 0;
    int maxPlayers = 4;
    int idClientMaster = 0;
    short port = 4242;
    //TODO: TMP RAW DATA
    auto entity = new LobbyCard(port, lobbyId, maxPlayers, idClientMaster);

    return std::shared_ptr<Engine::Entity>(entity);
}

void SocketParser::updateLobbyFromTcp(std::shared_ptr<Engine::Entity> &lobby, const std::vector<int> &in)
{
    //TODO: TMP RAW DATA (Get it from the "in")
    int connectedPlayers = 1;
    //TODO: TMP RAW DATA
    auto sprites = lobby->getComponents<Engine::SpriteComponent>();

    for (int i = 1; i < connectedPlayers + 1; ++i)
        sprites.at(i)->getSprite()->setRect({Engine::Box<int>({STARSHIP_WIDTH * i, 0}, {STARSHIP_WIDTH, STARSHIP_HEIGHT})});
}