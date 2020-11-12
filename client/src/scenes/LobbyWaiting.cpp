//
// Created by paul on 11/10/20.
//

#include <entities/LobbyCard.hpp>
#include <systems/TextSystem.hpp>
#include "scenes/SceneType.hpp"
#include "scenes/LobbyWaiting.hpp"
#include "systems/DrawSystem.hpp"
#include "systems/MouseSystem.hpp"
#include "systems/ButtonSystem.hpp"
#include "systems/ParallaxSystem.hpp"
#include "systems/MoveSystem.hpp"
#include "systems/AnimationSystem.hpp"
#include "systems/MusicSystem.hpp"
#include "systems/WindowResizeSystem.hpp"
#include "systems/PlayerAndStarshipSystem.hpp"
#include "components/AnimationComponent.hpp"
#include "entities/Button.hpp"
#include "entities/PlayerAndStarshipEntity.hpp"

void goToInGamesScene(std::shared_ptr<Engine::AScene> &lobbyWaiting)
{
    Engine::SceneRequest request(Engine::QueryType::SWITCH_SCENE, SceneType::GAME);

    lobbyWaiting->pushRequest(request);
}

void goBackToCreateLobby(std::shared_ptr<Engine::AScene> &lobbyWaiting)
{
    Engine::SceneRequest request(Engine::QueryType::SWITCH_SCENE, SceneType::CREATE_LOBBY);

    lobbyWaiting->pushRequest(request);
}

LobbyWaiting::LobbyWaiting(std::shared_ptr<Engine::AWindow> &window, std::shared_ptr<Engine::AEvents> &events, std::shared_ptr<NetworkAccess> &server)
    : _window(window), _events(events), _server(server), Engine::AScene(SceneType::LOBBY_WAITING)
{
    this->initSystems();
    this->initEntities();
}

void LobbyWaiting::initEntities()
{
    auto goBackButtonSprite = std::make_unique<SpriteSFML>(GO_BACK_BUTTON_PATH);
    std::shared_ptr<Engine::Entity> goBackButtonEngine = std::make_shared<Engine::Button>(Engine::Point<float>{GO_BACK_BUTTON_POSITION_X, GO_BACK_BUTTON_POSITION_Y}, Engine::Point<float>{GO_BACK_BUTTON_WIDTH, GO_BACK_BUTTON_HEIGHT}, std::move(goBackButtonSprite), &goBackToCreateLobby, std::shared_ptr<Engine::AScene>(this));
    goBackButtonEngine->getComponent<Engine::AnimationComponent>()->addAnimation(Engine::ButtonComponent::ButtonState::IDLE, {Engine::Box<float>({GO_BACK_BUTTON_X_IDLE, GO_BACK_BUTTON_Y}, {GO_BACK_BUTTON_WIDTH, GO_BACK_BUTTON_HEIGHT})});
    goBackButtonEngine->getComponent<Engine::AnimationComponent>()->addAnimation(Engine::ButtonComponent::ButtonState::HOVER, {Engine::Box<float>({GO_BACK_BUTTON_X_HOVER, GO_BACK_BUTTON_Y}, {GO_BACK_BUTTON_WIDTH, GO_BACK_BUTTON_HEIGHT})});
    goBackButtonEngine->getComponent<Engine::AnimationComponent>()->addAnimation(Engine::ButtonComponent::ButtonState::CLICKED, {Engine::Box<float>({GO_BACK_BUTTON_X_CLICKED, GO_BACK_BUTTON_Y}, {GO_BACK_BUTTON_WIDTH, GO_BACK_BUTTON_HEIGHT})});

    auto playButtonSprite = std::make_unique<SpriteSFML>(PLAY_BUTTON_PATH);
    std::shared_ptr<Engine::Entity> playButtonEngine = std::make_shared<Engine::Button>(Engine::Point<float>{870, 900}, Engine::Point<float>{PLAY_BUTTON_WIDTH, PLAY_BUTTON_HEIGHT}, std::move(playButtonSprite), &goToInGamesScene, std::shared_ptr<Engine::AScene>(this));
    playButtonEngine->getComponent<Engine::AnimationComponent>()->addAnimation(Engine::ButtonComponent::ButtonState::IDLE, {Engine::Box<float>({PLAY_BUTTON_X_IDLE, PLAY_BUTTON_Y}, {PLAY_BUTTON_WIDTH, PLAY_BUTTON_HEIGHT})});
    playButtonEngine->getComponent<Engine::AnimationComponent>()->addAnimation(Engine::ButtonComponent::ButtonState::HOVER, {Engine::Box<float>({PLAY_BUTTON_X_HOVER, PLAY_BUTTON_Y}, {PLAY_BUTTON_WIDTH, PLAY_BUTTON_HEIGHT})});
    playButtonEngine->getComponent<Engine::AnimationComponent>()->addAnimation(Engine::ButtonComponent::ButtonState::CLICKED, {Engine::Box<float>({PLAY_BUTTON_X_CLICKED, PLAY_BUTTON_Y}, {PLAY_BUTTON_WIDTH, PLAY_BUTTON_HEIGHT})});

    this->spawnEntity(goBackButtonEngine);
    this->spawnEntity(playButtonEngine);

    //TODO: remove the following temporary lines
    std::shared_ptr<Engine::Entity> playerAndStarShipCard = std::make_shared<PlayerAndStarshipEntity>("Player 1");
    playerAndStarShipCard->getComponent<Engine::TransformComponent>()->setPos({535, 100});
    this->spawnEntity(playerAndStarShipCard);

    std::shared_ptr<Engine::Entity> playerAndStarShipCard2 = std::make_shared<PlayerAndStarshipEntity>("Player 2");
    playerAndStarShipCard2->getComponent<Engine::TransformComponent>()->setPos({535, 300});
    this->spawnEntity(playerAndStarShipCard2);
}

void LobbyWaiting::initSystems()
{
    auto scene = std::shared_ptr<Engine::AScene>(this);
    auto draw = std::make_unique<Engine::DrawSystem>(this->_window);
    auto text = std::make_unique<Engine::TextSystem>(this->_window);
    auto mouse = std::make_unique<Engine::MouseSystem>(this->_events);
    auto btn = std::make_unique<Engine::ButtonSystem>();
    auto animation = std::make_unique<Engine::AnimationSystem>();
    auto parallax = std::make_unique<Engine::ParallaxSystem>();
    auto move = std::make_unique<Engine::MoveSystem>();
    auto music = std::make_unique<Engine::MusicSystem>();
    auto window = std::make_unique<Engine::WindowResizeSystem>(this->_window);
    auto playerAndStarshipSystem = std::make_unique<PlayerAndStarshipSystem>(this->_server, this->_events, scene);

    this->_systems.push_back(std::move(draw));
    this->_systems.push_back(std::move(text));
    this->_systems.push_back(std::move(mouse));
    this->_systems.push_back(std::move(btn));
    this->_systems.push_back(std::move(animation));
    this->_systems.push_back(std::move(parallax));
    this->_systems.push_back(std::move(move));
    this->_systems.push_back(std::move(music));
    this->_systems.push_back(std::move(window));
    this->_systems.push_back(std::move(playerAndStarshipSystem));
}

std::shared_ptr<Engine::AWindow> LobbyWaiting::getWindow() const
{
    return _window;
}

