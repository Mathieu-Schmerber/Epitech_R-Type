//
// Created by mathi on 30/10/2020.
//

#include <iostream>
#include <sfml/SpriteSfml.hpp>
#include "sceneManagement/SceneManager.hpp"
#include "systems/DrawSystem.hpp"
#include "systems/MouseSystem.hpp"
#include "systems/ParallaxSystem.hpp"
#include "systems/AnimationSystem.hpp"
#include "systems/MusicSystem.hpp"
#include "scenes/HowToPlay.hpp"
#include "entities/Button.hpp"
#include "entities/Drawable.hpp"
#include "entities/ParallaxSlide.hpp"
#include "components/AnimationComponent.hpp"
#include "tools/Geometry.hpp"
#include "sfml/MusicSFML.hpp"
#include "entities/Music.hpp"

HowToPlay::HowToPlay(std::shared_ptr<Engine::AWindow> &window, std::shared_ptr<Engine::AEvents> &events)
    : _window(window), _events(events), Engine::AScene(SceneType::HOW_TO_PLAY)
{
    this->initSystems();
    this->initEntities();
}

void HowToPlay::initEntities()
{
    auto goBackButtonSprite = std::make_unique<SpriteSFML>(GO_BACK_BUTTON_PATH);
    auto goBackButtonEngine = new Engine::Button({GO_BACK_BUTTON_POSITION_X, GO_BACK_BUTTON_POSITION_Y}, std::move(goBackButtonSprite), &goToMenuScene, std::shared_ptr<Engine::AScene>(this));
    goBackButtonEngine->getComponent<Engine::AnimationComponent>()->addAnimation("idle", {Engine::Box<int>({GO_BACK_BUTTON_X_IDLE, GO_BACK_BUTTON_Y}, {GO_BACK_BUTTON_WIDTH, GO_BACK_BUTTON_HEIGHT})});
    goBackButtonEngine->getComponent<Engine::AnimationComponent>()->addAnimation("hover", {Engine::Box<int>({GO_BACK_BUTTON_X_HOVER, GO_BACK_BUTTON_Y}, {GO_BACK_BUTTON_WIDTH, GO_BACK_BUTTON_HEIGHT})});
    goBackButtonEngine->getComponent<Engine::AnimationComponent>()->addAnimation("clicked", {Engine::Box<int>({GO_BACK_BUTTON_X_CLICKED, GO_BACK_BUTTON_Y}, {GO_BACK_BUTTON_WIDTH, GO_BACK_BUTTON_HEIGHT})});

    this->spawnEntity(std::shared_ptr<Engine::Button>(goBackButtonEngine));
}

void HowToPlay::initSystems()
{
    auto draw = std::make_unique<Engine::DrawSystem>(this->_window);
    auto mouse = std::make_unique<Engine::MouseSystem>(this->_events);
    auto animation = std::make_unique<Engine::AnimationSystem>();
    auto parallax = std::make_unique<Engine::ParallaxSystem>();
    auto music = std::make_unique<Engine::MusicSystem>();

    this->_systems.push_back(std::move(draw));
    this->_systems.push_back(std::move(mouse));
    this->_systems.push_back(std::move(animation));
    this->_systems.push_back(std::move(parallax));
    this->_systems.push_back(std::move(music));
}

std::shared_ptr<Engine::AWindow> HowToPlay::getWindow() const
{
    return _window;
}
