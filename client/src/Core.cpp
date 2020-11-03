//
// Created by mathi on 29/10/2020.
//

#include "Core.hpp"

#include <memory>

#include "scenes/MainMenu.hpp"
#include "scenes/Settings.hpp"
#include "entities/Button.hpp"
#include "sfml/GraphicalSFML.hpp"
#include "sfml/WindowSFML.hpp"
#include "sfml/SpriteSfml.hpp"
#include "sfml/EventsSFML.hpp"
#include "scenes/GroupId.hpp"
#include "scenes/Groups.hpp"

Core::Core()
{
    this->_graph = std::make_unique<GraphicalSFML>();
    this->_graph->setWindow(std::make_shared<WindowSFML>(std::string("r-type"), std::make_pair(1920, 1080)));
    this->_graph->setEvents(std::make_shared<EventsSFML>(_graph->getWindow()));
    this->_server = std::make_unique<Engine::AServer>("", 0);
    this->_timer = std::make_unique<Engine::Timer>();
    this->_sceneManager = std::make_unique<Engine::SceneManager>();
}

void Core::setupGroups()
{
    auto p = std::make_shared<ParallaxGroup>();

    this->_sceneManager->addGroup(GroupId::MENU_PARALLAX, std::dynamic_pointer_cast<Engine::AEntityGroup>(p));
    this->_sceneManager->setAccessGroup(SceneType::MAIN_MENU, GroupId::MENU_PARALLAX);
    this->_sceneManager->setAccessGroup(SceneType::SETTINGS, GroupId::MENU_PARALLAX);
}

void Core::initScenes()
{
    this->_sceneManager->addScene(std::move(std::make_unique<MainMenu>(this->_graph->getWindow(), this->_graph->getEvents())));
    this->_sceneManager->addScene(std::move(std::make_unique<Settings>(this->_graph->getWindow(), this->_graph->getEvents())));
    this->setupGroups();
    this->_sceneManager->switchScene(SceneType::MAIN_MENU);
}

void Core::start()
{
    this->initScenes();
    _graph->getWindow()->open();
    this->_graph->getWindow()->setFrameRate(60);
    while (_graph->getWindow()->isOpen())
        run();
}

void Core::run()
{
    this->_sceneManager->handleSceneRequests();
    this->_sceneManager->handleTime(this->_timer->deltatime());
    this->_sceneManager->getCurrent()->update();
    _graph->getEvents()->update();
    _graph->getWindow()->display();
}