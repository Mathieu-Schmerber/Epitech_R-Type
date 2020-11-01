//
// Created by mathi on 29/10/2020.
//

#include "Core.hpp"
#include "scenes/MainMenu.hpp"
#include "entities/Button.hpp"
#include "sfml/GraphicalSFML.hpp"
#include "sfml/WindowSFML.hpp"

Core::Core()
{
    printf("Create core\n");
    auto window = new WindowSFML("r-type", {1920, 1080});

    this->_graph = std::make_shared<GraphicalSFML>();
    this->_graph->setWindow(std::unique_ptr<WindowSFML>(window));

    this->_server = new Engine::AServer("", 0);
    Engine::SceneManager::setGraph(std::weak_ptr(_graph));
    Engine::SceneManager::setServer(this->_server);
}

void Core::start()
{
    auto mainMenu = Engine::SceneManager::createScene(new MainMenu());
    auto btn = std::make_unique<Button>(std::pair<int, int>{0, 0});

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
