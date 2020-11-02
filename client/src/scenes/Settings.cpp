//
// Created by mathi on 02/11/2020.
//

#include <iostream>
#include <sfml/SpriteSfml.hpp>
#include "SceneManager.hpp"
#include "systems/DrawSystem.hpp"
#include "systems/MouseSystem.hpp"
#include "systems/ParallaxSystem.hpp"
#include "scenes/Settings.hpp"
#include "entities/ParallaxSlide.hpp"
#include "entities/Drawable.hpp"

Settings::Settings(std::shared_ptr<Engine::AWindow> &window, std::shared_ptr<Engine::AEvents> &events)
        : _window(window), _events(events), Engine::AScene(SceneType::SETTINGS)
{
    this->initSystems();
    this->initEntities();
}

void Settings::initEntities()
{
    auto settingsBackgroundSprite = std::make_unique<SpriteSFML>(SETTINGS_BACKGROUND_PATH);
    auto settingsBackgroundEngine = new Engine::Drawable({SETTINGS_BACKGROUND_POSITION_X, SETTINGS_BACKGROUND_POSITION_Y}, std::move(settingsBackgroundSprite));

    this->spawnEntity(std::shared_ptr<Engine::Drawable>(settingsBackgroundEngine));
}

void Settings::initSystems()
{
    auto draw = std::make_unique<Engine::DrawSystem>(this->_window);
    auto mouse = std::make_unique<Engine::MouseSystem>(this->_events);
    auto parallax = std::make_unique<Engine::ParallaxSystem>();

    this->_systems.push_back(std::move(draw));
    this->_systems.push_back(std::move(mouse));
    this->_systems.push_back(std::move(parallax));
}