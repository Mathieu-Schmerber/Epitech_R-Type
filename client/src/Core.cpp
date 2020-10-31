//
// Created by mathi on 29/10/2020.
//

#include <iostream>
#include "Core.hpp"
#include "scenes/MainMenu.hpp"
#include "entities/Button.hpp"
#include "sfml/WindowSFML.hpp"

Core::Core()
{
    this->_window = new WindowSFML("", {1920, 1080});
    this->_server = new Engine::AServer("", 0);
    Engine::SceneManager::setWindow(this->_window);
    Engine::SceneManager::setServer(this->_server);
}

void Core::start()
{
    auto mainMenu = Engine::SceneManager::createScene(new MainMenu());
    auto btn = std::make_unique<Button>(std::pair<int, int>{0, 0});

    mainMenu->spawnEntity(std::move(btn));
    Engine::SceneManager::switchScene(SceneType::MAIN_MENU);
    while (true) {
        Engine::SceneManager::getCurrent()->update();

    }
}