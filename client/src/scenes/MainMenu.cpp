//
// Created by mathi on 30/10/2020.
//

#include <iostream>
#include <sfml/SpriteSfml.hpp>
#include "SceneManager.hpp"
#include "systems/DrawSystem.hpp"
#include "systems/MouseSystem.hpp"
#include "scenes/MainMenu.hpp"
#include "entities/Button.hpp"

void playCallback(std::shared_ptr<Engine::AScene> &menu)
{
    std::cout << "Play" << std::endl;
}

MainMenu::MainMenu(std::shared_ptr<Engine::AWindow> &window, std::shared_ptr<Engine::AEvents> &events)
: _window(window), _events(events), Engine::AScene(SceneType::MAIN_MENU)
{
    this->initSystems();
    this->initEntities();
}

void MainMenu::initEntities()
{
    auto sprite = std::make_unique<SpriteSFML>("../../client/assets/images/background/background_1.png");
    auto playBtn = new Engine::Button({0, 0}, std::move(sprite), &playCallback,std::shared_ptr<Engine::AScene>(this));

    this->spawnEntity(std::shared_ptr<Engine::Button>(playBtn));
}

void MainMenu::initSystems()
{
    auto draw = std::make_unique<Engine::DrawSystem>(this->_window);
    auto mouse = std::make_unique<Engine::MouseSystem>(this->_events);

    this->_systems.push_back(std::move(draw));
    this->_systems.push_back(std::move(mouse));
}