//
// Created by mathieu on 30/10/2020.
//

#include "systems/MoveSystem.hpp"
#include "sfml/SpriteSfml.hpp"
#include "sfml/MusicSFML.hpp"
#include "systems/DrawSystem.hpp"
#include "systems/WindowResizeSystem.hpp"
#include "systems/ButtonSystem.hpp"
#include "systems/TextSystem.hpp"
#include "systems/MouseSystem.hpp"
#include "systems/ParallaxSystem.hpp"
#include "systems/AnimationSystem.hpp"
#include "scenes/LobbyList.hpp"
#include "entities/Button.hpp"
#include "entities/Music.hpp"

void goToCreateLobbyScene(std::shared_ptr<Engine::AScene> &lobby)
{
    Engine::SceneRequest request(Engine::QueryType::SWITCH_SCENE, SceneType::CREATE_LOBBY);

    lobby->pushRequest(request);
}

void scrollDownLobby(std::shared_ptr<Engine::AScene> &lobby)
{
    auto lobbyObject = std::dynamic_pointer_cast<LobbyList>(lobby);
    auto lobbySystem = dynamic_cast<LobbySystem *>(lobbyObject->getLobbySystem().get());

    lobbySystem->scrollDownLobbies();
}

void scrollUpLobby(std::shared_ptr<Engine::AScene> &lobby)
{
    auto lobbyObject = std::dynamic_pointer_cast<LobbyList>(lobby);
    auto lobbySystem = dynamic_cast<LobbySystem *>(lobbyObject->getLobbySystem().get());

    lobbySystem->scrollUpLobbies();
}

void goToInGameScene(std::shared_ptr<Engine::AScene> &lobby)
{
    Engine::SceneRequest request(Engine::QueryType::SWITCH_SCENE, SceneType::GAME);

    lobby->pushRequest(request);
}

LobbyList::LobbyList(std::shared_ptr<Engine::AWindow> &window, std::shared_ptr<Engine::AEvents> &events, std::shared_ptr<NetworkAccess> &server)
: _window(window), _events(events), _server(server), Engine::AScene(SceneType::LOBBY_LIST)
{
    this->initSystems();
    this->initEntities();
}

void LobbyList::initEntities()
{
    auto goBackButtonSprite = std::make_unique<SpriteSFML>(GO_BACK_BUTTON_PATH);
    std::shared_ptr<Engine::Entity> goBackButtonEngine = std::make_shared<Engine::Button>(Engine::Point<double>{GO_BACK_BUTTON_POSITION_X, GO_BACK_BUTTON_POSITION_Y}, Engine::Point<double>{GO_BACK_BUTTON_WIDTH, GO_BACK_BUTTON_HEIGHT}, std::move(goBackButtonSprite), &goToMenuScene, std::shared_ptr<Engine::AScene>(this));
    goBackButtonEngine->getComponent<Engine::AnimationComponent>()->addAnimation(Engine::ButtonComponent::ButtonState::IDLE, {Engine::Box<double>({GO_BACK_BUTTON_X_IDLE, GO_BACK_BUTTON_Y}, {GO_BACK_BUTTON_WIDTH, GO_BACK_BUTTON_HEIGHT})});
    goBackButtonEngine->getComponent<Engine::AnimationComponent>()->addAnimation(Engine::ButtonComponent::ButtonState::HOVER, {Engine::Box<double>({GO_BACK_BUTTON_X_HOVER, GO_BACK_BUTTON_Y}, {GO_BACK_BUTTON_WIDTH, GO_BACK_BUTTON_HEIGHT})});
    goBackButtonEngine->getComponent<Engine::AnimationComponent>()->addAnimation(Engine::ButtonComponent::ButtonState::CLICKED, {Engine::Box<double>({GO_BACK_BUTTON_X_CLICKED, GO_BACK_BUTTON_Y}, {GO_BACK_BUTTON_WIDTH, GO_BACK_BUTTON_HEIGHT})});

    auto goUpButtonSprite = std::make_unique<SpriteSFML>(GO_UP_BUTTON_PATH);
    std::shared_ptr<Engine::Entity> goUpButtonEngine = std::make_shared<Engine::Button>(Engine::Point<double>{1385, 60}, Engine::Point<double>{GO_UP_BUTTON_WIDTH, GO_UP_BUTTON_HEIGHT}, std::move(goUpButtonSprite), &scrollUpLobby, std::shared_ptr<Engine::AScene>(this));
    goUpButtonEngine->getComponent<Engine::AnimationComponent>()->addAnimation(Engine::ButtonComponent::ButtonState::IDLE, {Engine::Box<double>({GO_UP_BUTTON_X_IDLE, GO_UP_BUTTON_Y}, {GO_UP_BUTTON_WIDTH, GO_UP_BUTTON_HEIGHT})});
    goUpButtonEngine->getComponent<Engine::AnimationComponent>()->addAnimation(Engine::ButtonComponent::ButtonState::HOVER, {Engine::Box<double>({GO_UP_BUTTON_X_HOVER, GO_UP_BUTTON_Y}, {GO_UP_BUTTON_WIDTH, GO_UP_BUTTON_HEIGHT})});
    goUpButtonEngine->getComponent<Engine::AnimationComponent>()->addAnimation(Engine::ButtonComponent::ButtonState::CLICKED, {Engine::Box<double>({GO_UP_BUTTON_X_CLICKED, GO_UP_BUTTON_Y}, {GO_UP_BUTTON_WIDTH, GO_UP_BUTTON_HEIGHT})});

    auto goDownButtonSprite = std::make_unique<SpriteSFML>(GO_DOWN_BUTTON_PATH);
    std::shared_ptr<Engine::Entity> goDownButtonEngine = std::make_shared<Engine::Button>(Engine::Point<double>{1385, 896}, Engine::Point<double>{GO_DOWN_BUTTON_WIDTH, GO_DOWN_BUTTON_HEIGHT}, std::move(goDownButtonSprite), &scrollDownLobby, std::shared_ptr<Engine::AScene>(this));
    goDownButtonEngine->getComponent<Engine::AnimationComponent>()->addAnimation(Engine::ButtonComponent::ButtonState::IDLE, {Engine::Box<double>({GO_DOWN_BUTTON_X_IDLE, GO_NEXT_BUTTON_Y}, {GO_DOWN_BUTTON_WIDTH, GO_DOWN_BUTTON_HEIGHT})});
    goDownButtonEngine->getComponent<Engine::AnimationComponent>()->addAnimation(Engine::ButtonComponent::ButtonState::HOVER, {Engine::Box<double>({GO_DOWN_BUTTON_X_HOVER, GO_NEXT_BUTTON_Y}, {GO_DOWN_BUTTON_WIDTH, GO_DOWN_BUTTON_HEIGHT})});
    goDownButtonEngine->getComponent<Engine::AnimationComponent>()->addAnimation(Engine::ButtonComponent::ButtonState::CLICKED, {Engine::Box<double>({GO_DOWN_BUTTON_X_CLICKED, GO_NEXT_BUTTON_Y}, {GO_DOWN_BUTTON_WIDTH, GO_DOWN_BUTTON_HEIGHT})});

    auto createLobbySprite = std::make_unique<SpriteSFML>(CREATE_LOBBY_BUTTON_PATH);
    std::shared_ptr<Engine::Entity> createLobbyButtonEngine = std::make_shared<Engine::Button>(Engine::Point<double>{1700, 30}, Engine::Point<double>{CREATE_LOBBY_BUTTON_WIDTH, CREATE_LOBBY_BUTTON_HEIGHT}, std::move(createLobbySprite), &goToCreateLobbyScene, std::shared_ptr<Engine::AScene>(this));
    createLobbyButtonEngine->getComponent<Engine::AnimationComponent>()->addAnimation(Engine::ButtonComponent::ButtonState::IDLE, {Engine::Box<double>({CREATE_LOBBY_BUTTON_X_IDLE, CREATE_LOBBY_BUTTON_Y}, {CREATE_LOBBY_BUTTON_WIDTH, CREATE_LOBBY_BUTTON_HEIGHT})});
    createLobbyButtonEngine->getComponent<Engine::AnimationComponent>()->addAnimation(Engine::ButtonComponent::ButtonState::HOVER, {Engine::Box<double>({CREATE_LOBBY_BUTTON_X_HOVER, GO_NEXT_BUTTON_Y}, {CREATE_LOBBY_BUTTON_WIDTH, CREATE_LOBBY_BUTTON_HEIGHT})});
    createLobbyButtonEngine->getComponent<Engine::AnimationComponent>()->addAnimation(Engine::ButtonComponent::ButtonState::CLICKED, {Engine::Box<double>({CREATE_LOBBY_BUTTON_X_CLICKED, CREATE_LOBBY_BUTTON_Y}, {CREATE_LOBBY_BUTTON_WIDTH, CREATE_LOBBY_BUTTON_HEIGHT})});

    this->spawnEntity(goBackButtonEngine);
    this->spawnEntity(goUpButtonEngine);
    this->spawnEntity(goDownButtonEngine);
    this->spawnEntity(createLobbyButtonEngine);
}

void LobbyList::initSystems()
{
    auto scene = std::shared_ptr<Engine::AScene>(this);
    auto draw = std::make_unique<Engine::DrawSystem>(this->_window);
    auto text = std::make_unique<Engine::TextSystem>(this->_window);
    auto mouse = std::make_unique<Engine::MouseSystem>(this->_events);
    auto btn = std::make_unique<Engine::ButtonSystem>();
    auto animation = std::make_unique<Engine::AnimationSystem>();
    auto parallax = std::make_unique<Engine::ParallaxSystem>();
    auto move = std::make_unique<Engine::MoveSystem>();
    auto window = std::make_unique<Engine::WindowResizeSystem>(this->_window);
    auto lobby = std::make_unique<LobbySystem>(this->_server, this->_events, scene);

    this->_systems.push_back(std::move(draw));
    this->_systems.push_back(std::move(text));
    this->_systems.push_back(std::move(mouse));
    this->_systems.push_back(std::move(btn));
    this->_systems.push_back(std::move(animation));
    this->_systems.push_back(std::move(parallax));
    this->_systems.push_back(std::move(move));
    this->_systems.push_back(std::move(window));
    this->_systems.push_back(std::move(lobby));
    //lobby MUST BE THE LAST COMPONENT to get lobby System (see getSystem method)
}

std::shared_ptr<Engine::AWindow> LobbyList::getWindow() const
{
    return _window;
}

const std::unique_ptr<Engine::System> &LobbyList::getLobbySystem() const
{
    return _systems.back();
}
