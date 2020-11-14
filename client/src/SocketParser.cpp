//
// Created by mathi on 06/11/2020.
//

#include <fstream>
#include "SocketParser.hpp"
#include "entities/LobbyCard.hpp"
#include "components/NetworkComponent.hpp"

SocketParser::SocketParser()
{
    this->_pool = std::make_unique<Engine::AssetPool>("../../client/assets");
    this->_timer = std::make_unique<Engine::Timer>();
    this->_deltatime = 0;
    this->_serverTimer = std::make_unique<Engine::Timer>();
    this->_serverDelta = 0;
    this->_serverUpdate = false;
}

Engine::Point<int> SocketParser::lerp(Engine::Point<int> a, Engine::Point<int> b, double time)
{
    double factor = 1;

    if (time <= factor)
        return {(int)(a.x * (1 - time * factor) + b.x * time * factor), (int)(a.y * (1 - time * factor) + b.y * time * factor)};
    return b;
}

bool SocketParser::shouldTeleport(Engine::Point<int> a, Engine::Point<int> b, Engine::Point<int> size)
{
    double tolerance = 40;

    return (abs(sqrt(pow(b.x - a.x, 2)) - tolerance) >= (double)(size.x * 0.5) ||
            abs(sqrt(pow(b.y - a.y, 2)) - tolerance) >= (double)(size.y * 0.5));
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

std::shared_ptr<Engine::Entity> SocketParser::unparseUdpEntity(const std::vector<int> &in) const
{
    if (in.at(0) == 1) {
        return createSpriteEntity(in);
    } else {
        return createTextEntity(in);
    }
}

std::shared_ptr<Engine::Entity> SocketParser::createTextEntity(const std::vector<int> &in) const
{
    Engine::TextComponent *text = nullptr;
    auto entity = new Engine::Entity();

    if (in.size() < 10)
        return nullptr;

    entity->addComponent<Engine::NetworkComponent>(in.at(1));
    entity->addComponent<Engine::TransformComponent>(Engine::Point<double>{static_cast<double>(in.at(4)), static_cast<double>(in.at(5))}, in.at(6));
    entity->addComponent<Engine::TextComponent>();
    text = entity->getComponent<Engine::TextComponent>();
    std::shared_ptr<Engine::AFont> font = std::make_shared<FontSFML>(_pool->getPathFromIndex(in.at(2)));
    std::ifstream ifs(_pool->getPathFromIndex(in.at(3)));
    std::string content((std::istreambuf_iterator<char>(ifs)), (std::istreambuf_iterator<char>()));
    std::unique_ptr<Engine::AText> txt = std::make_unique<TextSFML>(content, font, in.at(7));
    txt->setLetterSpacing(in.at(7));
    text->setText(std::move(txt));
    text->setLayer(in.at(9));

    return std::shared_ptr<Engine::Entity>(entity);
}

std::shared_ptr<Engine::Entity> SocketParser::createSpriteEntity(const std::vector<int> &in) const
{
    auto entity = new Engine::Entity();
    Engine::SpriteComponent *sprite = nullptr;

    if (in.size() < 10)
        return nullptr;
    entity->addComponent<Engine::NetworkComponent>(in.at(1));
    entity->addComponent<Engine::TransformComponent>(Engine::Point<double>{static_cast<double>(in.at(2)), static_cast<double>(in.at(3))}, in.at(4));
    entity->addComponent<Engine::SpriteComponent>();
    sprite = entity->getComponent<Engine::SpriteComponent>();
    auto spr = std::make_unique<SpriteSFML>(_pool->getPathFromIndex(in.at(5)));
    sprite->setDisplay(std::move(spr));
    sprite->getSprite()->setRect(
            {static_cast<double>(in.at(6)), static_cast<double>(in.at(7)), static_cast<double>(in.at(8)),
             static_cast<double>(in.at(9))});
    return std::shared_ptr<Engine::Entity>(entity);
}

void SocketParser::updateEntityFromUdp(std::shared_ptr<Engine::Entity> &entity, const std::vector<int> &in) const
{
    if (in.at(0) == 1) {
        updateSpriteEntity(entity, in);
    } else {
        updateTextEntity(entity, in);
    }
}

void SocketParser::updateTextEntity(std::shared_ptr<Engine::Entity> &entity, const std::vector<int> &in) const
{
    auto text = entity->getComponent<Engine::TextComponent>();

    entity->addComponent<Engine::NetworkComponent>(in.at(1));
    entity->getComponent<Engine::TransformComponent>()->setPos(Engine::Point<double>{static_cast<double>(in.at(4)), static_cast<double>(in.at(5))});
    entity->getComponent<Engine::TransformComponent>()->setRotation(in.at(6));

    std::shared_ptr<Engine::AFont> font = std::make_shared<FontSFML>(_pool->getPathFromIndex(in.at(2)));
    std::ifstream ifs(_pool->getPathFromIndex(in.at(3)));
    std::string content((std::istreambuf_iterator<char>(ifs)), (std::istreambuf_iterator<char>()));
    std::unique_ptr<Engine::AText> txt = std::make_unique<TextSFML>(content, font, in.at(7));
    txt->setLetterSpacing(in.at(7));
    text->setText(std::move(txt));
    text->setLayer(in.at(9));
}

void SocketParser::updateSpriteEntity(const std::shared_ptr<Engine::Entity> &entity, const std::vector<int> &in) const
{
    auto sprite = entity->getComponent<Engine::SpriteComponent>();
    Engine::Point<int> initialPos = static_cast<Engine::Point<int>>(entity->getComponent<Engine::TransformComponent>()->getPos());
    auto smooth = lerp(initialPos, {in.at(2), in.at(3)}, _deltatime);

    if (shouldTeleport(initialPos, {in.at(2), in.at(3)}, {in.at(7), in.at(9)}))
        smooth = Engine::Point<int>{in.at(2), in.at(3)};
    entity->getComponent<Engine::TransformComponent>()->setPos(static_cast<Engine::Point<double>>(smooth));
    entity->getComponent<Engine::TransformComponent>()->setRotation(in.at(4));
    sprite->getSprite()->setRect(
            {static_cast<double>(in.at(6)), static_cast<double>(in.at(7)), static_cast<double>(in.at(8)),
             static_cast<double>(in.at(9))});
    sprite->setLayer(in.at(10));
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
        sprites.at(i)->getSprite()->setRect({Engine::Box<double>({static_cast<double>(STARSHIP_WIDTH) * i, 0}, {STARSHIP_WIDTH, STARSHIP_HEIGHT})});
}

void SocketParser::refreshTimer(bool dataChanged)
{
    this->_serverUpdate = dataChanged;
    if (dataChanged)
        this->_serverDelta = this->_serverTimer->deltatime();
    this->_deltatime = this->_timer->deltatime();
}