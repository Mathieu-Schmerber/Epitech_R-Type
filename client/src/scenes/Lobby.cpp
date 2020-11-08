//
// Created by mathieu on 30/10/2020.
//

#include "systems/MoveSystem.hpp"
#include "sfml/SpriteSfml.hpp"
#include "sfml/MusicSFML.hpp"
#include "sfml/FontSFML.hpp"
#include "systems/DrawSystem.hpp"
#include "systems/TextSystem.hpp"
#include "systems/MouseSystem.hpp"
#include "systems/ParallaxSystem.hpp"
#include "systems/AnimationSystem.hpp"
#include "systems/MusicSystem.hpp"
#include "scenes/Lobby.hpp"
#include "entities/Button.hpp"
#include "entities/Drawable.hpp"
#include "enumerations/ButtonState.hpp"
#include "scenes/SceneEnum.hpp"
#include "entities/LobbyCard.hpp"
#include "components/LobbyComponent.hpp"

void enterLobby(std::shared_ptr<Engine::AScene> &lobby)
{
    auto lobbyObject = std::dynamic_pointer_cast<Lobby>(lobby);

}

void goToInGameScene(std::shared_ptr<Engine::AScene> &lobby)
{
    Engine::SceneRequest request(Engine::QueryType::SWITCH_SCENE, SceneType::GAME);

    lobby->pushRequest(request);
}


Lobby::Lobby(std::shared_ptr<Engine::AWindow> &window, std::shared_ptr<Engine::AEvents> &events)
    : _window(window), _events(events), Engine::AScene(SceneType::LOBBY)
{
    this->initSystems();
    this->initEntities();
}

void Lobby::initEntities()
{
    auto goBackButtonSprite = std::make_unique<SpriteSFML>(GO_BACK_BUTTON_PATH);
    auto goBackButtonEngine =  std::make_shared<Engine::Button>(Engine::Point<int>{GO_BACK_BUTTON_POSITION_X, GO_BACK_BUTTON_POSITION_Y}, std::move(goBackButtonSprite), &goToMenuScene, std::shared_ptr<Engine::AScene>(this));
    goBackButtonEngine->getComponent<Engine::AnimationComponent>()->addAnimation(Engine::ButtonState::IDLE, {Engine::Box<int>({GO_BACK_BUTTON_X_IDLE, GO_BACK_BUTTON_Y}, {GO_BACK_BUTTON_WIDTH, GO_BACK_BUTTON_HEIGHT})});
    goBackButtonEngine->getComponent<Engine::AnimationComponent>()->addAnimation(Engine::ButtonState::HOVER, {Engine::Box<int>({GO_BACK_BUTTON_X_HOVER, GO_BACK_BUTTON_Y}, {GO_BACK_BUTTON_WIDTH, GO_BACK_BUTTON_HEIGHT})});
    goBackButtonEngine->getComponent<Engine::AnimationComponent>()->addAnimation(Engine::ButtonState::CLICKED, {Engine::Box<int>({GO_BACK_BUTTON_X_CLICKED, GO_BACK_BUTTON_Y}, {GO_BACK_BUTTON_WIDTH, GO_BACK_BUTTON_HEIGHT})});

    auto goNextButtonSprite = std::make_unique<SpriteSFML>(GO_NEXT_BUTTON_PATH);
    auto goNextButtonEngine =  std::make_shared<Engine::Button>(Engine::Point<int>{GO_NEXT_BUTTON_POSITION_X, GO_NEXT_BUTTON_POSITION_Y}, std::move(goNextButtonSprite), &goToInGameScene, std::shared_ptr<Engine::AScene>(this));
    goNextButtonEngine->getComponent<Engine::AnimationComponent>()->addAnimation(Engine::ButtonState::IDLE, {Engine::Box<int>({GO_NEXT_BUTTON_X_IDLE, GO_NEXT_BUTTON_Y}, {GO_NEXT_BUTTON_WIDTH, GO_NEXT_BUTTON_HEIGHT})});
    goNextButtonEngine->getComponent<Engine::AnimationComponent>()->addAnimation(Engine::ButtonState::HOVER, {Engine::Box<int>({GO_NEXT_BUTTON_X_HOVER, GO_NEXT_BUTTON_Y}, {GO_NEXT_BUTTON_WIDTH, GO_NEXT_BUTTON_HEIGHT})});
    goNextButtonEngine->getComponent<Engine::AnimationComponent>()->addAnimation(Engine::ButtonState::CLICKED, {Engine::Box<int>({GO_NEXT_BUTTON_X_CLICKED, GO_NEXT_BUTTON_Y}, {GO_NEXT_BUTTON_WIDTH, GO_NEXT_BUTTON_HEIGHT})});

    this->spawnEntity(std::shared_ptr<Engine::Button>(goBackButtonEngine));
    this->spawnEntity(std::shared_ptr<Engine::Button>(goNextButtonEngine));

    std::shared_ptr<Engine::AFont> font = std::make_shared<FontSFML>(PIXEBOY_FONT_PATH);


    //TMP TODO Emilien implement call to recover lobbycomponent and client//
    auto _lobby1 = Engine::LobbyComponent(4242, 0, 4, 2, 5);
    _lobbies.push_back(_lobby1);
    auto _lobby2 = Engine::LobbyComponent(4242, 1, 4, 0, 7);
    _lobbies.push_back(_lobby2);
    auto _lobby3 = Engine::LobbyComponent(4242, 2, 1, 0, 8);
    _lobbies.push_back(_lobby3);
    auto _lobby4 = Engine::LobbyComponent(4242, 3, 4, 3, 9);
    _lobbies.push_back(_lobby4);
    //TMP//

    int relativePositionLobbyCardY = 60;
    for (auto &lobby : _lobbies) {
        auto lobbyCardFirst = std::make_shared<LobbyCard>(Engine::Point<int>{535, relativePositionLobbyCardY}, lobby, font, &enterLobby,
            std::shared_ptr<Engine::AScene>(this), 1);
        _lobbiesEngines.push_back(lobbyCardFirst);
        this->spawnEntity(std::shared_ptr<LobbyCard>(lobbyCardFirst));
        relativePositionLobbyCardY += 250;
    }
}

void Lobby::initSystems()
{
    auto draw = std::make_unique<Engine::DrawSystem>(this->_window);
    auto text = std::make_unique<Engine::TextSystem>(this->_window);
    auto mouse = std::make_unique<Engine::MouseSystem>(this->_events);
    auto animation = std::make_unique<Engine::AnimationSystem>();
    auto parallax = std::make_unique<Engine::ParallaxSystem>();
    auto move = std::make_unique<Engine::MoveSystem>();
    auto music = std::make_unique<Engine::MusicSystem>();

    this->_systems.push_back(std::move(draw));
    this->_systems.push_back(std::move(text));
    this->_systems.push_back(std::move(mouse));
    this->_systems.push_back(std::move(animation));
    this->_systems.push_back(std::move(parallax));
    this->_systems.push_back(std::move(move));
    this->_systems.push_back(std::move(music));
}

std::shared_ptr<Engine::AWindow> Lobby::getWindow() const
{
    return _window;
}

std::vector<Engine::LobbyComponent> Lobby::getLobbies() const
{
    return _lobbies;
}

std::vector<std::shared_ptr<LobbyCard>> Lobby::getLobbiesEngines() const
{
    return _lobbiesEngines;
}
