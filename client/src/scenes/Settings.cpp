//
// Created by mathi on 02/11/2020.
//

#include <sfml/SpriteSfml.hpp>
#include "SceneManager.hpp"
#include "systems/DrawSystem.hpp"
#include "systems/MouseSystem.hpp"
#include "systems/ParallaxSystem.hpp"
#include "scenes/Settings.hpp"
#include "entities/ParallaxSlide.hpp"

Settings::Settings(std::shared_ptr<Engine::AWindow> &window, std::shared_ptr<Engine::AEvents> &events)
        : _window(window), _events(events), Engine::AScene(SceneType::SETTINGS)
{
    this->initSystems();
    this->initEntities();
}

void Settings::initEntities()
{
    auto spriteA = std::make_unique<SpriteSFML>("../../client/assets/images/background/background_1.png");
    auto spriteB = std::make_unique<SpriteSFML>("../../client/assets/images/background/background_1.png");
    auto slideA = new Engine::ParallaxSlide({0, 0}, {-1920, 0}, {-10, 0}, std::move(spriteA));
    auto slideB = new Engine::ParallaxSlide({1920, 0}, {0, 0}, {-10, 0}, std::move(spriteB));

    this->spawnEntity(std::shared_ptr<Engine::ParallaxSlide>(slideA));
    this->spawnEntity(std::shared_ptr<Engine::ParallaxSlide>(slideB));
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