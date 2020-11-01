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
    this->_graph = std::make_shared<GraphicalSFML>();
    this->_graph->setWindow(std::make_shared<WindowSFML>(std::string("r-type"), std::make_pair(1920, 1080)));

    this->_server = new Engine::AServer("", 0);
    Engine::SceneManager::setGraph(std::weak_ptr(_graph));
    Engine::SceneManager::setServer(this->_server);
}

void Core::start()
{
    auto mainMenu = Engine::SceneManager::createScene(new MainMenu());
    auto sprite = std::unique_ptr<SpriteSFML>(new SpriteSFML("../../client/assets/images/background/background_1.png"));
    auto btn = std::make_unique<Engine::Button>(Engine::Point<int>{0, 0}, std::move(sprite), nullptr);

    mainMenu->spawnEntity(std::move(btn));
    Engine::SceneManager::switchScene(SceneType::MAIN_MENU);

    _graph->getWindow()->open();
    while (_graph->getWindow()->isOpen()) {
        run();
    }
}

void Core::run()
{
    Engine::SceneManager::getCurrent()->update();
    _graph->getWindow()->display();
}