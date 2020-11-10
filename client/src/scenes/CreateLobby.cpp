//
// Created by Paul on 11/10/20.
//

#include "entities/Text.hpp"
#include "systems/MoveSystem.hpp"
#include "sfml/SpriteSfml.hpp"
#include "sfml/MusicSFML.hpp"
#include "sfml/TextSFML.hpp"
#include "sfml/FontSFML.hpp"
#include "systems/DrawSystem.hpp"
#include "systems/WindowResizeSystem.hpp"
#include "systems/ButtonSystem.hpp"
#include "systems/TextSystem.hpp"
#include "systems/MouseSystem.hpp"
#include "systems/ParallaxSystem.hpp"
#include "systems/AnimationSystem.hpp"
#include "systems/MusicSystem.hpp"
#include "entities/Button.hpp"
#include "entities/Music.hpp"
#include "scenes/CreateLobby.hpp"
#include "scenes/SceneEnum.hpp"

void goBackToLobbyList(std::shared_ptr<Engine::AScene> &createLobby)
{
    Engine::SceneRequest request(Engine::QueryType::SWITCH_SCENE, SceneType::LOBBY_LIST);

    createLobby->pushRequest(request);
}

void goToLobbyWaiting(std::shared_ptr<Engine::AScene> &createLobby)
{

}

void increaseNbOfClientsCb(std::shared_ptr<Engine::AScene> &createLobby)
{
    auto createLobbyObject = std::dynamic_pointer_cast<CreateLobby>(createLobby);
    auto &text = createLobbyObject->getTextNbPlayerMax()->getComponent<Engine::TextComponent>()->getText();
    auto string = text->toStdString();
    auto nb = std::atoi(string.substr(20, 21).c_str());

    if (nb < 9) {
        string.back() = std::to_string(nb + 1).front();
        text->setString(string);
    }
}

void decreaseNbOfClientsCb(std::shared_ptr<Engine::AScene> &createLobby)
{
    auto createLobbyObject = std::dynamic_pointer_cast<CreateLobby>(createLobby);
    auto &text = createLobbyObject->getTextNbPlayerMax()->getComponent<Engine::TextComponent>()->getText();
    auto string = text->toStdString();
    auto nb = std::atoi(string.substr(20, 21).c_str());

    if (nb > 1) {
        string.back() = std::to_string(nb - 1).front();
        text->setString(string);
    }
}

CreateLobby::CreateLobby(std::shared_ptr<Engine::AWindow> &window, std::shared_ptr<Engine::AEvents> &events, std::shared_ptr<NetworkAccess> &server)
    : _window(window), _events(events), _server(server), Engine::AScene(SceneType::CREATE_LOBBY)
{
    this->initSystems();
    this->initEntities();
}

void CreateLobby::initEntities()
{
    auto goBackButtonSprite = std::make_unique<SpriteSFML>(GO_BACK_BUTTON_PATH);
    std::shared_ptr<Engine::Entity> goBackButtonEngine = std::make_shared<Engine::Button>(Engine::Point<int>{GO_BACK_BUTTON_POSITION_X, GO_BACK_BUTTON_POSITION_Y}, Engine::Point<int>{GO_BACK_BUTTON_WIDTH, GO_BACK_BUTTON_HEIGHT}, std::move(goBackButtonSprite), &goBackToLobbyList, std::shared_ptr<Engine::AScene>(this));
    goBackButtonEngine->getComponent<Engine::AnimationComponent>()->addAnimation(Engine::ButtonComponent::ButtonState::IDLE, {Engine::Box<int>({GO_BACK_BUTTON_X_IDLE, GO_BACK_BUTTON_Y}, {GO_BACK_BUTTON_WIDTH, GO_BACK_BUTTON_HEIGHT})});
    goBackButtonEngine->getComponent<Engine::AnimationComponent>()->addAnimation(Engine::ButtonComponent::ButtonState::HOVER, {Engine::Box<int>({GO_BACK_BUTTON_X_HOVER, GO_BACK_BUTTON_Y}, {GO_BACK_BUTTON_WIDTH, GO_BACK_BUTTON_HEIGHT})});
    goBackButtonEngine->getComponent<Engine::AnimationComponent>()->addAnimation(Engine::ButtonComponent::ButtonState::CLICKED, {Engine::Box<int>({GO_BACK_BUTTON_X_CLICKED, GO_BACK_BUTTON_Y}, {GO_BACK_BUTTON_WIDTH, GO_BACK_BUTTON_HEIGHT})});

    auto goUpButtonSprite = std::make_unique<SpriteSFML>(GO_UP_BUTTON_PATH);
    std::shared_ptr<Engine::Entity> goUpButtonEngine = std::make_shared<Engine::Button>(Engine::Point<int>{1310, 432}, Engine::Point<int>{GO_UP_BUTTON_WIDTH, GO_UP_BUTTON_HEIGHT}, std::move(goUpButtonSprite), &increaseNbOfClientsCb, std::shared_ptr<Engine::AScene>(this));
    goUpButtonEngine->getComponent<Engine::AnimationComponent>()->addAnimation(Engine::ButtonComponent::ButtonState::IDLE, {Engine::Box<int>({GO_UP_BUTTON_X_IDLE, GO_UP_BUTTON_Y}, {GO_UP_BUTTON_WIDTH, GO_UP_BUTTON_HEIGHT})});
    goUpButtonEngine->getComponent<Engine::AnimationComponent>()->addAnimation(Engine::ButtonComponent::ButtonState::HOVER, {Engine::Box<int>({GO_UP_BUTTON_X_HOVER, GO_UP_BUTTON_Y}, {GO_UP_BUTTON_WIDTH, GO_UP_BUTTON_HEIGHT})});
    goUpButtonEngine->getComponent<Engine::AnimationComponent>()->addAnimation(Engine::ButtonComponent::ButtonState::CLICKED, {Engine::Box<int>({GO_UP_BUTTON_X_CLICKED, GO_UP_BUTTON_Y}, {GO_UP_BUTTON_WIDTH, GO_UP_BUTTON_HEIGHT})});

    auto goDownButtonSprite = std::make_unique<SpriteSFML>(GO_DOWN_BUTTON_PATH);
    std::shared_ptr<Engine::Entity> goDownButtonEngine = std::make_shared<Engine::Button>(Engine::Point<int>{1310, 626}, Engine::Point<int>{GO_DOWN_BUTTON_WIDTH, GO_DOWN_BUTTON_HEIGHT}, std::move(goDownButtonSprite), &decreaseNbOfClientsCb, std::shared_ptr<Engine::AScene>(this));
    goDownButtonEngine->getComponent<Engine::AnimationComponent>()->addAnimation(Engine::ButtonComponent::ButtonState::IDLE, {Engine::Box<int>({GO_DOWN_BUTTON_X_IDLE, GO_NEXT_BUTTON_Y}, {GO_DOWN_BUTTON_WIDTH, GO_DOWN_BUTTON_HEIGHT})});
    goDownButtonEngine->getComponent<Engine::AnimationComponent>()->addAnimation(Engine::ButtonComponent::ButtonState::HOVER, {Engine::Box<int>({GO_DOWN_BUTTON_X_HOVER, GO_NEXT_BUTTON_Y}, {GO_DOWN_BUTTON_WIDTH, GO_DOWN_BUTTON_HEIGHT})});
    goDownButtonEngine->getComponent<Engine::AnimationComponent>()->addAnimation(Engine::ButtonComponent::ButtonState::CLICKED, {Engine::Box<int>({GO_DOWN_BUTTON_X_CLICKED, GO_NEXT_BUTTON_Y}, {GO_DOWN_BUTTON_WIDTH, GO_DOWN_BUTTON_HEIGHT})});

    auto createLobbySprite = std::make_unique<SpriteSFML>(CREATE_LOBBY_BUTTON_PATH);
    std::shared_ptr<Engine::Entity> createLobbyButtonEngine = std::make_shared<Engine::Button>(Engine::Point<int>{900, 670}, Engine::Point<int>{GO_DOWN_BUTTON_WIDTH, GO_DOWN_BUTTON_HEIGHT}, std::move(createLobbySprite),&goToLobbyWaiting, std::shared_ptr<Engine::AScene>(this));
    createLobbyButtonEngine->getComponent<Engine::AnimationComponent>()->addAnimation(Engine::ButtonComponent::ButtonState::IDLE, {Engine::Box<int>({CREATE_LOBBY_BUTTON_X_IDLE, CREATE_LOBBY_BUTTON_Y}, {CREATE_LOBBY_BUTTON_WIDTH, CREATE_LOBBY_BUTTON_HEIGHT})});
    createLobbyButtonEngine->getComponent<Engine::AnimationComponent>()->addAnimation(Engine::ButtonComponent::ButtonState::HOVER, {Engine::Box<int>({CREATE_LOBBY_BUTTON_X_HOVER, GO_NEXT_BUTTON_Y}, {CREATE_LOBBY_BUTTON_WIDTH, CREATE_LOBBY_BUTTON_HEIGHT})});
    createLobbyButtonEngine->getComponent<Engine::AnimationComponent>()->addAnimation(Engine::ButtonComponent::ButtonState::CLICKED, {Engine::Box<int>({CREATE_LOBBY_BUTTON_X_CLICKED, CREATE_LOBBY_BUTTON_Y}, {CREATE_LOBBY_BUTTON_WIDTH, CREATE_LOBBY_BUTTON_HEIGHT})});

    std::shared_ptr<Engine::AFont> font = std::make_shared<FontSFML>(PIXEBOY_FONT_PATH);
    auto nbMaxOfClientsText = std::make_unique<TextSFML>("Number of players : 1", font, 100);
    std::shared_ptr<Engine::Entity> nbMaxOfClientsTextEngine = std::make_shared<Engine::Text>(Engine::Point<int>{547, 486}, std::move(nbMaxOfClientsText));
    _textNbPlayerMax = nbMaxOfClientsTextEngine;

    this->spawnEntity(goBackButtonEngine);
    this->spawnEntity(goUpButtonEngine);
    this->spawnEntity(goDownButtonEngine);
    this->spawnEntity(createLobbyButtonEngine);
    this->spawnEntity(nbMaxOfClientsTextEngine);
}

void CreateLobby::initSystems()
{
    auto draw = std::make_unique<Engine::DrawSystem>(this->_window);
    auto text = std::make_unique<Engine::TextSystem>(this->_window);
    auto mouse = std::make_unique<Engine::MouseSystem>(this->_events);
    auto btn = std::make_unique<Engine::ButtonSystem>();
    auto animation = std::make_unique<Engine::AnimationSystem>();
    auto parallax = std::make_unique<Engine::ParallaxSystem>();
    auto move = std::make_unique<Engine::MoveSystem>();
    auto music = std::make_unique<Engine::MusicSystem>();
    auto window = std::make_unique<Engine::WindowResizeSystem>(this->_window);

    this->_systems.push_back(std::move(draw));
    this->_systems.push_back(std::move(text));
    this->_systems.push_back(std::move(mouse));
    this->_systems.push_back(std::move(btn));
    this->_systems.push_back(std::move(animation));
    this->_systems.push_back(std::move(parallax));
    this->_systems.push_back(std::move(move));
    this->_systems.push_back(std::move(music));
    this->_systems.push_back(std::move(window));
}


std::shared_ptr<Engine::AWindow> CreateLobby::getWindow() const
{
    return _window;
}

std::shared_ptr<Engine::Entity> CreateLobby::getTextNbPlayerMax() const
{
    return _textNbPlayerMax;
}
