//
// Created by mathi on 29/10/2020.
//

#include "Core.hpp"

#include <memory>
#include <iostream>

#include "tools/Geometry.hpp"
#include "scenes/MainMenu.hpp"
#include "entities/Button.hpp"
#include "sfml/GraphicalSFML.hpp"
#include "sfml/WindowSFML.hpp"
#include "sfml/SpriteSfml.hpp"

Core::Core()
{
    this->_graph = std::make_unique<GraphicalSFML>();
    this->_graph->setWindow(std::make_shared<WindowSFML>(std::string("r-type"), std::make_pair(1920, 1080)));
    this->_server = std::make_unique<Engine::AServer>("", 0);
    this->_sceneManager = std::make_unique<Engine::SceneManager>();
}

void Core::initScenes()
{
    this->_sceneManager->addScene(std::move(std::make_unique<MainMenu>(this->_graph->getWindow(), this->_graph->getEvents())));
    this->_sceneManager->switchScene(SceneType::MAIN_MENU);
}

void Core::start()
{
    this->initScenes();
    _graph->getWindow()->open();
    while (_graph->getWindow()->isOpen()) {
        run();
    }
}

void Core::run()
{
    this->_sceneManager->handleSwitchRequests();
    this->_sceneManager->getCurrent()->update();
    _graph->getWindow()->display();
}