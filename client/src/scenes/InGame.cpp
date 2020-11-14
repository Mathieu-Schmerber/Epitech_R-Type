//
// Created by mathi on 06/11/2020.
//

#include "systems/QuitSystemInGame.hpp"
#include "systems/WindowResizeSystem.hpp"
#include "systems/AnimationSystem.hpp"
#include "systems/MouseSystem.hpp"
#include "systems/ButtonSystem.hpp"
#include "sfml/SpriteSfml.hpp"
#include "entities/Button.hpp"
#include "scenes/SceneType.hpp"
#include "scenes/InGame.hpp"
#include "systems/DrawSystem.hpp"
#include "systems/MusicSystem.hpp"
#include "systems/ClientNetworkSystem.hpp"
#include "entities/Music.hpp"
#include "scenes/SceneEnum.hpp"
#include "components/SpriteComponent.hpp"

void backToMainMenu(std::shared_ptr<Engine::AScene> &inGame)
{
    Engine::SceneRequest request(Engine::QueryType::SWITCH_SCENE, SceneType::MAIN_MENU);

   inGame->pushRequest(request);
}

InGame::InGame(std::shared_ptr<Engine::AWindow> &window, std::shared_ptr<Engine::AEvents> &events, std::shared_ptr<NetworkAccess> &server)
: _window(window), _events(events), _server(server), Engine::AScene(SceneType::GAME)
{
    this->initSystems();
    this->initEntities();
}

void InGame::initEntities()
{
    auto quitButtonSprite = std::make_unique<SpriteSFML>(QUIT_BUTTON_PATH);

    std::shared_ptr<Engine::Entity> quitButtonEngine = std::make_shared<Engine::Button>(Engine::Point<double>{867, 511.5}, Engine::Point<double>{QUIT_BUTTON_WIDTH, QUIT_BUTTON_HEIGHT}, std::move(quitButtonSprite), &backToMainMenu, std::shared_ptr<Engine::AScene>(this), 99);
    quitButtonEngine->getComponent<Engine::AnimationComponent>()->addAnimation(Engine::ButtonComponent::ButtonState::IDLE, {Engine::Box<double>({QUIT_BUTTON_X_IDLE, QUIT_BUTTON_Y}, {QUIT_BUTTON_WIDTH, QUIT_BUTTON_HEIGHT})});
    quitButtonEngine->getComponent<Engine::AnimationComponent>()->addAnimation(Engine::ButtonComponent::ButtonState::HOVER, {Engine::Box<double>({QUIT_BUTTON_X_HOVER, QUIT_BUTTON_Y}, {QUIT_BUTTON_WIDTH, QUIT_BUTTON_HEIGHT})});
    quitButtonEngine->getComponent<Engine::AnimationComponent>()->addAnimation(Engine::ButtonComponent::ButtonState::CLICKED, {Engine::Box<double>({QUIT_BUTTON_X_CLICKED, QUIT_BUTTON_Y}, {QUIT_BUTTON_WIDTH, QUIT_BUTTON_HEIGHT})});
    quitButtonEngine->getComponent<Engine::SpriteComponent>()->hasToBeDraw(true);

    _quitButton = quitButtonEngine;

    this->spawnEntity(quitButtonEngine);
}

void InGame::initSystems()
{
    auto scene = std::shared_ptr<Engine::AScene>(this);
    auto draw = std::make_unique<Engine::DrawSystem>(this->_window);
    auto music = std::make_unique<Engine::MusicSystem>();
    auto btn = std::make_unique<Engine::ButtonSystem>();
    auto animation = std::make_unique<Engine::AnimationSystem>();
    auto mouse = std::make_unique<Engine::MouseSystem>(this->_events);
    auto network = std::make_unique<ClientNetworkSystem>(this->_server, this->_events, scene);
    auto quitSystem = std::make_unique<QuitSystemInGame>(this->_events, scene);
    auto window = std::make_unique<Engine::WindowResizeSystem>(this->_window);

    this->_systems.push_back(std::move(draw));
    this->_systems.push_back(std::move(mouse));
    this->_systems.push_back(std::move(btn));
    this->_systems.push_back(std::move(quitSystem));
    this->_systems.push_back(std::move(animation));
    this->_systems.push_back(std::move(music));
    this->_systems.push_back(std::move(network));
    this->_systems.push_back(std::move(window));
}

void InGame::onFocus()
{
    //TODO: remove the following temporary line
    this->_server->setClientId(0);
    //TODO: remove the following temporary line
    this->_server->openSockets();
}

void InGame::onExit()
{
    this->_entities.clear();
}

std::shared_ptr<Engine::Entity> InGame::getQuitButton() const
{
    return _quitButton;
}
