//
// Created by mathi on 29/10/2020.
//

#include <iostream>
#include "scenes/MainMenu.hpp"
#include "Core.hpp"

Core::Core()
{
    this->_window = new Engine::AWindow("", {1920, 1080});
    this->_server = new Engine::AServer("", 0);
    Engine::SceneManager::setWindow(this->_window);
    Engine::SceneManager::setServer(this->_server);
}

void Core::start()
{
    Engine::SceneManager::createScene(new MainMenu());
    Engine::SceneManager::switchScene(SceneType::MAIN_MENU);

    Engine::SceneManager::getCurrent()->init();
    Engine::SceneManager::getCurrent()->update();
}