//
// Created by mathi on 30/10/2020.
//

#include <iostream>
#include <sfml/SpriteSfml.hpp>
#include "SceneManager.hpp"
#include "systems/DrawSystem.hpp"
#include "systems/MouseSystem.hpp"
#include "systems/ParallaxSystem.hpp"
#include "scenes/MainMenu.hpp"
#include "entities/Button.hpp"
#include "entities/ParallaxSlide.hpp"

void playCallback(std::shared_ptr<Engine::AScene> &menu)
{
    menu->requestSwitch(SceneType::SETTINGS);
}

MainMenu::MainMenu(std::shared_ptr<Engine::AWindow> &window, std::shared_ptr<Engine::AEvents> &events)
: _window(window), _events(events), Engine::AScene(SceneType::MAIN_MENU)
{
    this->initSystems();
    this->initEntities();
}

void MainMenu::initEntities()
{
    auto menuParralaxA = std::make_unique<SpriteSFML>(MENU_PARALLAX_PATH);
    auto menuParralaxB = std::make_unique<SpriteSFML>(MENU_PARALLAX_PATH);
    auto slideA = new Engine::ParallaxSlide({0, 0}, {-1920, 0}, {-10, 0}, std::move(menuParralaxA));
    auto slideB = new Engine::ParallaxSlide({1920, 0}, {0, 0}, {-10, 0}, std::move(menuParralaxB));

    auto rtypeLogoSprite = std::make_unique<SpriteSFML>(RTYPE_LOGO_PATH);
    auto rTypeLogoEngine = new Engine::Button({610, 50}, std::move(rtypeLogoSprite), &playCallback, std::shared_ptr<Engine::AScene>(this));

    auto startButtonSprite = std::make_unique<SpriteSFML>(START_BUTTON_PATH);
    auto startButtonEngine = new Engine::Button({846, 300}, std::move(startButtonSprite), &playCallback, std::shared_ptr<Engine::AScene>(this));

    auto settingsButtonSprite = std::make_unique<SpriteSFML>(SETTINGS_BUTTON_PATH);
    auto settingsButtonEngine = new Engine::Button({776, 500}, std::move(settingsButtonSprite), &playCallback, std::shared_ptr<Engine::AScene>(this));

    auto howToPlayButtonSprite = std::make_unique<SpriteSFML>(HOW_TO_PLAY_BUTTON_PATH);
    auto howToPlayButtonEngine = new Engine::Button({736, 700}, std::move(howToPlayButtonSprite), &playCallback, std::shared_ptr<Engine::AScene>(this));

    auto quitButtonSprite = std::make_unique<SpriteSFML>(QUIT_BUTTON_PATH);
    auto quitButtonEngine = new Engine::Button({867, 900}, std::move(quitButtonSprite), &playCallback, std::shared_ptr<Engine::AScene>(this));

    this->spawnEntity(std::shared_ptr<Engine::ParallaxSlide>(slideA));
    this->spawnEntity(std::shared_ptr<Engine::ParallaxSlide>(slideB));
    this->spawnEntity(std::shared_ptr<Engine::Button>(startButtonEngine));
    this->spawnEntity(std::shared_ptr<Engine::Button>(settingsButtonEngine));
    this->spawnEntity(std::shared_ptr<Engine::Button>(howToPlayButtonEngine));
    this->spawnEntity(std::shared_ptr<Engine::Button>(quitButtonEngine));
    this->spawnEntity(std::shared_ptr<Engine::Button>(rTypeLogoEngine));
}

void MainMenu::initSystems()
{
    auto draw = std::make_unique<Engine::DrawSystem>(this->_window);
    auto mouse = std::make_unique<Engine::MouseSystem>(this->_events);
    auto parallax = std::make_unique<Engine::ParallaxSystem>();

    this->_systems.push_back(std::move(draw));
    this->_systems.push_back(std::move(mouse));
    this->_systems.push_back(std::move(parallax));
}