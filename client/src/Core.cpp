//
// Created by mathi on 29/10/2020.
//

#include <memory>

#include "Core.hpp"
#include "scenes/MainMenu.hpp"
#include "scenes/Settings.hpp"
#include "scenes/HowToPlay.hpp"
#include "scenes/InGame.hpp"
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
    this->_server = std::make_shared<NetworkAccess>("127.0.0.1", 4242, 4343);
    this->_timer = std::make_unique<Engine::Timer>();
    this->_sceneManager = std::make_unique<Engine::SceneManager>();
}

void Core::setupGroups()
{
    auto p = std::make_shared<ParallaxGroup>();
    auto m = std::make_shared<MusicGroup>();

    this->_sceneManager->addGroup(GroupId::MENU_PARALLAX, std::dynamic_pointer_cast<Engine::AEntityGroup>(p));
    this->_sceneManager->addGroup(GroupId::MENU_MUSIC, std::dynamic_pointer_cast<Engine::AEntityGroup>(m));
    this->_sceneManager->setAccessGroup(SceneType::MAIN_MENU, {GroupId::MENU_PARALLAX, GroupId::MENU_MUSIC});
    this->_sceneManager->setAccessGroup(SceneType::SETTINGS, {GroupId::MENU_PARALLAX, GroupId::MENU_MUSIC});
    this->_sceneManager->setAccessGroup(SceneType::HOW_TO_PLAY, {GroupId::MENU_PARALLAX, GroupId::MENU_MUSIC});
}

void Core::initScenes()
{
    this->_sceneManager->addScene(std::move(std::make_unique<MainMenu>(this->_graph->getWindow(), this->_graph->getEvents())));
    this->_sceneManager->addScene(std::move(std::make_unique<Settings>(this->_graph->getWindow(), this->_graph->getEvents())));
    this->_sceneManager->addScene(std::move(std::make_unique<HowToPlay>(this->_graph->getWindow(), this->_graph->getEvents())));
    this->_sceneManager->addScene(std::move(std::make_unique<InGame>(this->_graph->getWindow(), this->_graph->getEvents(), this->_server)));
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