//
// Created by mathi on 30/10/2020.
//

#include "sfml/SpriteSfml.hpp"
#include "sfml/MusicSFML.hpp"
#include "sceneManagement/SceneManager.hpp"
#include "systems/DrawSystem.hpp"
#include "systems/MouseSystem.hpp"
#include "systems/ButtonSystem.hpp"
#include "systems/ParallaxSystem.hpp"
#include "systems/MoveSystem.hpp"
#include "systems/AnimationSystem.hpp"
#include "systems/MusicSystem.hpp"
#include "systems/WindowResizeSystem.hpp"
#include "scenes/MainMenu.hpp"
#include "entities/Button.hpp"
#include "entities/Drawable.hpp"
#include "entities/Music.hpp"
#include "scenes/SceneEnum.hpp"

void goToLobbyListScene(std::shared_ptr<Engine::AScene> &menu)
{
    Engine::SceneRequest request(Engine::QueryType::SWITCH_SCENE, SceneType::LOBBY_LIST);

    menu->pushRequest(request);
}

void goToSettingsScene(std::shared_ptr<Engine::AScene> &menu)
{
    Engine::SceneRequest request(Engine::QueryType::SWITCH_SCENE, SceneType::SETTINGS);

    menu->pushRequest(request);
}

void goToHowToPlayScene(std::shared_ptr<Engine::AScene> &menu)
{
    Engine::SceneRequest request(Engine::QueryType::SWITCH_SCENE, SceneType::HOW_TO_PLAY);

    menu->pushRequest(request);
}

void quitGame(std::shared_ptr<Engine::AScene> &menu)
{
    auto mainMenu = std::dynamic_pointer_cast<MainMenu>(menu);

    mainMenu->getWindow()->close();
}

void emptyCallback(std::shared_ptr<Engine::AScene> &menu)
{

}

MainMenu::MainMenu(std::shared_ptr<Engine::AWindow> &window, std::shared_ptr<Engine::AEvents> &events)
: _window(window), _events(events), Engine::AScene(SceneType::MAIN_MENU)
{
    this->initSystems();
    this->initEntities();
}

void MainMenu::initEntities()
{
    auto rtypeLogoSprite = std::make_unique<SpriteSFML>(RTYPE_LOGO_PATH);
    std::shared_ptr<Engine::Entity> rTypeLogoEngine = std::make_shared<Engine::Drawable>(Engine::Point<double>{RTYPE_LOGO_POSITION_X, RTYPE_LOGO_POSITION_Y}, std::move(rtypeLogoSprite));

    auto startButtonSprite = std::make_unique<SpriteSFML>(START_BUTTON_PATH);
    std::shared_ptr<Engine::Entity> startButtonEngine = std::make_shared<Engine::Button>(Engine::Point<double>{START_BUTTON_POSITION_X, START_BUTTON_POSITION_Y}, Engine::Point<double>{START_BUTTON_WIDTH, START_BUTTON_HEIGHT}, std::move(startButtonSprite), &goToLobbyListScene, std::shared_ptr<Engine::AScene>(this));
    startButtonEngine->getComponent<Engine::AnimationComponent>()->addAnimation(Engine::ButtonComponent::ButtonState::IDLE, {Engine::Box<double>({START_BUTTON_X_IDLE, START_BUTTON_Y}, {START_BUTTON_WIDTH, START_BUTTON_HEIGHT})});
    startButtonEngine->getComponent<Engine::AnimationComponent>()->addAnimation(Engine::ButtonComponent::ButtonState::HOVER, {Engine::Box<double>({START_BUTTON_X_HOVER, START_BUTTON_Y}, {START_BUTTON_WIDTH, START_BUTTON_HEIGHT})});
    startButtonEngine->getComponent<Engine::AnimationComponent>()->addAnimation(Engine::ButtonComponent::ButtonState::CLICKED, {Engine::Box<double>({START_BUTTON_X_CLICKED, START_BUTTON_Y}, {START_BUTTON_WIDTH, START_BUTTON_HEIGHT})});

    auto settingsButtonSprite = std::make_unique<SpriteSFML>(SETTINGS_BUTTON_PATH);
    std::shared_ptr<Engine::Entity> settingsButtonEngine = std::make_shared<Engine::Button>(Engine::Point<double>{SETTINGS_BUTTON_POSITION_X, SETTINGS_BUTTON_POSITION_Y}, Engine::Point<double>{SETTINGS_BUTTON_WIDTH, SETTINGS_BUTTON_HEIGHT}, std::move(settingsButtonSprite), &goToSettingsScene, std::shared_ptr<Engine::AScene>(this));
    settingsButtonEngine->getComponent<Engine::AnimationComponent>()->addAnimation(Engine::ButtonComponent::ButtonState::IDLE, {Engine::Box<double>({SETTINGS_BUTTON_X_IDLE, SETTINGS_BUTTON_Y}, {SETTINGS_BUTTON_WIDTH, SETTINGS_BUTTON_HEIGHT})});
    settingsButtonEngine->getComponent<Engine::AnimationComponent>()->addAnimation(Engine::ButtonComponent::ButtonState::HOVER, {Engine::Box<double>({SETTINGS_BUTTON_X_HOVER, SETTINGS_BUTTON_Y}, {SETTINGS_BUTTON_WIDTH, SETTINGS_BUTTON_HEIGHT})});
    settingsButtonEngine->getComponent<Engine::AnimationComponent>()->addAnimation(Engine::ButtonComponent::ButtonState::CLICKED, {Engine::Box<double>({SETTINGS_BUTTON_X_CLICKED, SETTINGS_BUTTON_Y}, {SETTINGS_BUTTON_WIDTH, SETTINGS_BUTTON_HEIGHT})});

    auto howToPlayButtonSprite = std::make_unique<SpriteSFML>(HOW_TO_PLAY_BUTTON_PATH);
    std::shared_ptr<Engine::Entity> howToPlayButtonEngine = std::make_shared<Engine::Button>(Engine::Point<double>{HOW_TO_PLAY_BUTTON_POSITION_X, HOW_TO_PLAY_BUTTON_POSITION_Y}, Engine::Point<double>{HOW_TO_PLAY_BUTTON_WIDTH, HOW_TO_PLAY_BUTTON_HEIGHT}, std::move(howToPlayButtonSprite), &goToHowToPlayScene, std::shared_ptr<Engine::AScene>(this));
    howToPlayButtonEngine->getComponent<Engine::AnimationComponent>()->addAnimation(Engine::ButtonComponent::ButtonState::IDLE, {Engine::Box<double>({HOW_TO_PLAY_BUTTON_X_IDLE, HOW_TO_PLAY_BUTTON_Y}, {HOW_TO_PLAY_BUTTON_WIDTH, HOW_TO_PLAY_BUTTON_HEIGHT})});
    howToPlayButtonEngine->getComponent<Engine::AnimationComponent>()->addAnimation(Engine::ButtonComponent::ButtonState::HOVER, {Engine::Box<double>({HOW_TO_PLAY_BUTTON_X_HOVER, HOW_TO_PLAY_BUTTON_Y}, {HOW_TO_PLAY_BUTTON_WIDTH, HOW_TO_PLAY_BUTTON_HEIGHT})});
    howToPlayButtonEngine->getComponent<Engine::AnimationComponent>()->addAnimation(Engine::ButtonComponent::ButtonState::CLICKED, {Engine::Box<double>({HOW_TO_PLAY_BUTTON_X_CLICKED, HOW_TO_PLAY_BUTTON_Y}, {HOW_TO_PLAY_BUTTON_WIDTH, HOW_TO_PLAY_BUTTON_HEIGHT})});

    auto quitButtonSprite = std::make_unique<SpriteSFML>(QUIT_BUTTON_PATH);
    std::shared_ptr<Engine::Entity> quitButtonEngine = std::make_shared<Engine::Button>(Engine::Point<double>{QUIT_BUTTON_POSITION_X, QUIT_BUTTON_POSITION_Y}, Engine::Point<double>{QUIT_BUTTON_WIDTH, QUIT_BUTTON_HEIGHT}, std::move(quitButtonSprite), &quitGame, std::shared_ptr<Engine::AScene>(this));
    quitButtonEngine->getComponent<Engine::AnimationComponent>()->addAnimation(Engine::ButtonComponent::ButtonState::IDLE, {Engine::Box<double>({QUIT_BUTTON_X_IDLE, QUIT_BUTTON_Y}, {QUIT_BUTTON_WIDTH, QUIT_BUTTON_HEIGHT})});
    quitButtonEngine->getComponent<Engine::AnimationComponent>()->addAnimation(Engine::ButtonComponent::ButtonState::HOVER, {Engine::Box<double>({QUIT_BUTTON_X_HOVER, QUIT_BUTTON_Y}, {QUIT_BUTTON_WIDTH, QUIT_BUTTON_HEIGHT})});
    quitButtonEngine->getComponent<Engine::AnimationComponent>()->addAnimation(Engine::ButtonComponent::ButtonState::CLICKED, {Engine::Box<double>({QUIT_BUTTON_X_CLICKED, QUIT_BUTTON_Y}, {QUIT_BUTTON_WIDTH, QUIT_BUTTON_HEIGHT})});

    this->spawnEntity(startButtonEngine);
    this->spawnEntity(settingsButtonEngine);
    this->spawnEntity(howToPlayButtonEngine);
    this->spawnEntity(quitButtonEngine);
    this->spawnEntity(rTypeLogoEngine);
}

void MainMenu::initSystems()
{
    auto draw = std::make_unique<Engine::DrawSystem>(this->_window);
    auto mouse = std::make_unique<Engine::MouseSystem>(this->_events);
    auto btn = std::make_unique<Engine::ButtonSystem>();
    auto parallax = std::make_unique<Engine::ParallaxSystem>();
    auto move = std::make_unique<Engine::MoveSystem>();
    auto animation = std::make_unique<Engine::AnimationSystem>();
    auto music = std::make_unique<Engine::MusicSystem>();
    auto resize = std::make_unique<Engine::WindowResizeSystem>(this->_window);

    this->_systems.push_back(std::move(draw));
    this->_systems.push_back(std::move(mouse));
    this->_systems.push_back(std::move(btn));
    this->_systems.push_back(std::move(parallax));
    this->_systems.push_back(std::move(move));
    this->_systems.push_back(std::move(animation));
    this->_systems.push_back(std::move(music));
    this->_systems.push_back(std::move(resize));
}

std::shared_ptr<Engine::AWindow> MainMenu::getWindow() const
{
    return _window;
}
