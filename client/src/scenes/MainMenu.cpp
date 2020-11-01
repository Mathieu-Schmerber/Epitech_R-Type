//
// Created by mathi on 30/10/2020.
//

#include "systems/DrawSystem.hpp"
#include "SceneManager.hpp"
#include "scenes/MainMenu.hpp"

MainMenu::MainMenu() : Engine::AScene(SceneType::MAIN_MENU)
{
    auto draw = std::make_unique<Engine::DrawSystem>(Engine::SceneManager::getGraph()->getWindow());

    this->_systems.push_back(std::move(draw));
}