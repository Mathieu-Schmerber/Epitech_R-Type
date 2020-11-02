//
// Created by mathi on 02/11/2020.
//

#include <iostream>
#include <sfml/SpriteSfml.hpp>
#include "SceneManager.hpp"
#include "systems/DrawSystem.hpp"
#include "systems/MouseSystem.hpp"
#include "scenes/Settings.hpp"
#include "entities/Button.hpp"

void testCallback(std::shared_ptr<Engine::AScene> &settings)
{
    std::cout << "Test" << std::endl;
}

Settings::Settings(std::shared_ptr<Engine::AWindow> &window, std::shared_ptr<Engine::AEvents> &events)
        : _window(window), _events(events), Engine::AScene(SceneType::SETTINGS)
{
    this->initSystems();
    this->initEntities();
}

void Settings::initEntities()
{
    auto sprite = std::make_unique<SpriteSFML>("../../client/assets/images/buttons/start/start_button_idle_228x57.png");
    auto playBtn = new Engine::Button({50, 900}, std::move(sprite), &testCallback, std::shared_ptr<Engine::AScene>(this));

    this->spawnEntity(std::shared_ptr<Engine::Button>(playBtn));
}

void Settings::initSystems()
{
    auto draw = std::make_unique<Engine::DrawSystem>(this->_window);
    auto mouse = std::make_unique<Engine::MouseSystem>(this->_events);

    this->_systems.push_back(std::move(draw));
    this->_systems.push_back(std::move(mouse));
}