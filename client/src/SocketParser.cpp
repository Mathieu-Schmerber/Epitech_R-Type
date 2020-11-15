//
// Created by mathi on 06/11/2020.
//

#include <fstream>
#include "SocketParser.hpp"
#include "sfml/MusicSFML.hpp"
#include "sfml/SoundSFML.hpp"
#include "entities/LobbyCard.hpp"
#include "components/NetworkComponent.hpp"
#include "components/SoundComponent.hpp"
#include "components/MusicComponent.hpp"

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
    double tolerance = 60;

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

std::shared_ptr<Engine::Entity> SocketParser::unparseUdpEntity(const std::vector<int> &in)
{
    if (in.at(0) == 1) {
        return createSpriteEntity(in);
    } else {
        return createTextEntity(in);
    }
}

std::shared_ptr<Engine::Entity> SocketParser::createTextEntity(const std::vector<int> &in)
{
    Engine::TextComponent *text = nullptr;
    auto entity = new Engine::Entity();

    if (in.size() < 10)
        return nullptr;

    std::cout << in << std::endl;
    entity->addComponent<Engine::NetworkComponent>(in.at(1));
    entity->addComponent<Engine::TransformComponent>(Engine::Point<double>{static_cast<double>(in.at(4)), static_cast<double>(in.at(5))}, in.at(6));
    entity->addComponent<Engine::TextComponent>();
    text = entity->getComponent<Engine::TextComponent>();
    std::ifstream ifs(_pool->getPathFromIndex(in.at(2)));
    std::string content((std::istreambuf_iterator<char>(ifs)), (std::istreambuf_iterator<char>()));


    if (_fonts.find(this->_pool->getPathFromIndex(in.at(2))) == _fonts.end()) {
        _fonts[_pool->getPathFromIndex(in.at(2))] = std::make_shared<FontSFML>(_pool->getPathFromIndex(in.at(2)));
    }
    std::unique_ptr<Engine::AText> txt = std::make_unique<TextSFML>(content, _fonts.at(_pool->getPathFromIndex(in.at(2))), in.at(7));
    txt->setLetterSpacing(in.at(8));
    text->setText(std::move(txt));
    text->setLayer(in.at(9));
    text->getText()->setFillColor(Engine::Color({255, 255, 255, static_cast<unsigned char>(in.at(10))}));
    text->getText()->setOrigin(Engine::Point<double>({static_cast<double>(text->getText()->getSize().x / 2), static_cast<double>(text->getText()->getSize().y / 2)}));
    if (in.at(11) != -1) {
        if (in.at(11) == 1) {
            auto music = std::make_unique<MusicSFML>(_pool->getPathFromIndex(in.at(12)));
            entity->addComponent<Engine::MusicComponent>(std::move(music))->playMe(in.at(13));
        } else if (in.at(11) == 0) {
            auto sound = std::make_unique<SoundSFML>(_pool->getPathFromIndex(in.at(12)));
            entity->addComponent<Engine::SoundComponent>(std::move(sound))->playMe(in.at(13));
        }
    }
    return std::shared_ptr<Engine::Entity>(entity);
}

std::shared_ptr<Engine::Entity> SocketParser::createSpriteEntity(const std::vector<int> &in)
{
    auto entity = new Engine::Entity();
    Engine::SpriteComponent *sprite = nullptr;

    if (in.size() < 10)
        return nullptr;
    entity->addComponent<Engine::NetworkComponent>(in.at(1));
    entity->addComponent<Engine::TransformComponent>(Engine::Point<double>{static_cast<double>(in.at(2)), static_cast<double>(in.at(3))}, in.at(4));
    entity->addComponent<Engine::SpriteComponent>();
    sprite = entity->getComponent<Engine::SpriteComponent>();
    if (!Engine::Utils::isInMap(_textures, _pool->getPathFromIndex(in.at(5))))
        _textures[_pool->getPathFromIndex(in.at(5))] = std::make_shared<TextureSFML>(_pool->getPathFromIndex(in.at(5)));
    auto spr = std::make_unique<SpriteSFML>(_textures.at(_pool->getPathFromIndex(in.at(5))));
    sprite->setDisplay(std::move(spr));
    sprite->getSprite()->setRect(
            {static_cast<double>(in.at(6)), static_cast<double>(in.at(7)), static_cast<double>(in.at(8)),
             static_cast<double>(in.at(9))});
    if (in.at(11) != -1) {
        if (in.at(11) == 1) {
            auto music = std::make_unique<MusicSFML>(_pool->getPathFromIndex(in.at(12)));
            entity->addComponent<Engine::MusicComponent>(std::move(music))->playMe(in.at(13));
        } else if (in.at(11) == 0) {
            auto sound = std::make_unique<SoundSFML>(_pool->getPathFromIndex(in.at(12)));
            entity->addComponent<Engine::SoundComponent>(std::move(sound))->playMe(in.at(13));
        }
    }
    return std::shared_ptr<Engine::Entity>(entity);
}

void SocketParser::updateEntityFromUdp(std::shared_ptr<Engine::Entity> entity, const std::vector<int> &in) const
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

    entity->getComponent<Engine::TransformComponent>()->setPos(Engine::Point<double>{static_cast<double>(in.at(4)), static_cast<double>(in.at(5))});
    entity->getComponent<Engine::TransformComponent>()->setRotation(in.at(6));

    std::string file = _pool->getPathFromIndex(in.at(3));
    std::ifstream ifs(file);
    std::string content;
    if (ifs.fail() || file.substr(file.find_last_of('.') + 1) != "txt" || file == "null")
        content = "";
    else
        content = std::string((std::istreambuf_iterator<char>(ifs)), (std::istreambuf_iterator<char>()));

    text->getText()->setString(content);
    text->getText()->setCharacterSize(in.at(7));
    text->getText()->setLetterSpacing(in.at(8));

    text->setLayer(in.at(9));
    text->getText()->setFillColor(Engine::Color({255, 255, 255, static_cast<unsigned char>(in.at(10))}));
    text->getText()->setOrigin(Engine::Point<double>({static_cast<double>(text->getText()->getSize().x / 2), static_cast<double>(text->getText()->getSize().y / 2)}));
    if (in.at(11) != -1) {
        if (in.at(11) == 1) {
            entity->getComponent<Engine::MusicComponent>()->playMe(in.at(13));
            if (_pool->getPathFromIndex(in.at(12)) != entity->getComponent<Engine::MusicComponent>()->getMusic()->getFile()) {
                auto music = std::make_unique<MusicSFML>(_pool->getPathFromIndex(in.at(12)));
                entity->getComponent<Engine::MusicComponent>()->setMusic(std::move(music));
            }
        } else if (in.at(11) == 0) {
            entity->getComponent<Engine::SoundComponent>()->playMe(in.at(13));
            if (_pool->getPathFromIndex(in.at(12)) != entity->getComponent<Engine::SoundComponent>()->getSound()->getFile()) {
                auto sound = std::make_unique<SoundSFML>(_pool->getPathFromIndex(in.at(12)));
                entity->getComponent<Engine::SoundComponent>()->setSound(std::move(sound));
            }
        }
    }
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
    if (in.at(11) != -1) {
        if (in.at(11) == 1) {
            entity->getComponent<Engine::MusicComponent>()->playMe(in.at(13));
            if (_pool->getPathFromIndex(in.at(12)) != entity->getComponent<Engine::MusicComponent>()->getMusic()->getFile()) {
                auto music = std::make_unique<MusicSFML>(_pool->getPathFromIndex(in.at(12)));
                entity->getComponent<Engine::MusicComponent>()->setMusic(std::move(music));
            }
        } else if (in.at(11) == 0) {
            entity->getComponent<Engine::SoundComponent>()->playMe(in.at(13));
            if (_pool->getPathFromIndex(in.at(12)) != entity->getComponent<Engine::SoundComponent>()->getSound()->getFile()) {
                auto sound = std::make_unique<SoundSFML>(_pool->getPathFromIndex(in.at(12)));
                entity->getComponent<Engine::SoundComponent>()->setSound(std::move(sound));
            }
        }
    }
}

std::shared_ptr<Engine::Entity> SocketParser::unparseTcpLobby(const std::vector<int> &in)
{
    //TODO: TMP RAW DATA (Get it from the "in")
    int lobbyId = in.at(2);
    int maxPlayers = in.at(4);
    int idClientMaster = in.at(5);
    short port = in.at(3);
    //TODO: TMP RAW DATA
    auto entity = new LobbyCard(port, lobbyId, maxPlayers, idClientMaster);

    return std::shared_ptr<Engine::Entity>(entity);
}

void SocketParser::updateLobbyFromTcp(std::shared_ptr<Engine::Entity> &lobby, const std::vector<int> &in)
{
    int connectedPlayers = in.at(4);
    //TODO: TMP RAW DATA
    auto sprites = lobby->getComponents<Engine::SpriteComponent>();

    if (in.at(5) == 1)
        std::cout << "Game launched" << std::endl;
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
