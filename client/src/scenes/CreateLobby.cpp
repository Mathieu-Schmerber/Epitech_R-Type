//
// Created by Paul on 11/10/20.
//

#include <sfml/SpriteSfml.hpp>
#include "sfml/MusicSFML.hpp"
#include "systems/DrawSystem.hpp"
#include "systems/WindowResizeSystem.hpp"
#include "systems/ButtonSystem.hpp"
#include "systems/TextSystem.hpp"
#include "systems/MouseSystem.hpp"
#include "systems/ParallaxSystem.hpp"
#include "systems/MusicSystem.hpp"
#include "scenes/CreateLobby.hpp"
#include "entities/Button.hpp"
#include "entities/Music.hpp"
#include "scenes/SceneEnum.hpp"

CreateLobby::CreateLobby(std::shared_ptr<Engine::AWindow> &window, std::shared_ptr<Engine::AEvents> &events, std::shared_ptr<NetworkAccess> &server)
    : _window(window), _events(events), _server(server), Engine::AScene(SceneType::CREATE_LOBBY)
{
    this->initSystems();
    this->initEntities();
}

void CreateLobby::initEntities()
{

}

void CreateLobby::initSystems()
{
    auto draw = std::make_unique<Engine::DrawSystem>(this->_window);
    auto text = std::make_unique<Engine::TextSystem>(this->_window);
    auto mouse = std::make_unique<Engine::MouseSystem>(this->_events);
    auto btn = std::make_unique<Engine::ButtonSystem>();
    auto parallax = std::make_unique<Engine::ParallaxSystem>();
    auto music = std::make_unique<Engine::MusicSystem>();
    auto window = std::make_unique<Engine::WindowResizeSystem>(this->_window);

    this->_systems.push_back(std::move(draw));
    this->_systems.push_back(std::move(text));
    this->_systems.push_back(std::move(mouse));
    this->_systems.push_back(std::move(btn));
    this->_systems.push_back(std::move(parallax));
    this->_systems.push_back(std::move(music));
    this->_systems.push_back(std::move(window));
}

std::shared_ptr<Engine::AWindow> CreateLobby::getWindow() const
{
    return _window;
}