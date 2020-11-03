//
// Created by mathi on 30/10/2020.
//

#include <sfml/SpriteSfml.hpp>
#include "sceneManagement/SceneManager.hpp"
#include "systems/DrawSystem.hpp"
#include "systems/MouseSystem.hpp"
#include "systems/ParallaxSystem.hpp"
#include "systems/AnimationSystem.hpp"
#include "systems/MusicSystem.hpp"
#include "scenes/MainMenu.hpp"
#include "entities/Button.hpp"
#include "entities/Drawable.hpp"
#include "entities/ParallaxSlide.hpp"
#include "components/AnimationComponent.hpp"
#include "tools/Geometry.hpp"
#include "sfml/MusicSFML.hpp"
#include "entities/Music.hpp"

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
    auto rTypeLogoEngine = new Engine::Drawable({RTYPE_LOGO_POSITION_X, RTYPE_LOGO_POSITION_Y}, std::move(rtypeLogoSprite));

    auto startButtonSprite = std::make_unique<SpriteSFML>(START_BUTTON_PATH);
    auto startButtonEngine = new Engine::Button({START_BUTTON_POSITION_X, START_BUTTON_POSITION_Y}, std::move(startButtonSprite), &emptyCallback, std::shared_ptr<Engine::AScene>(this));
    startButtonEngine->getComponent<Engine::AnimationComponent>()->addAnimation("idle", {Engine::Box<int>({START_BUTTON_X_IDLE, START_BUTTON_Y}, {START_BUTTON_WIDTH, START_BUTTON_HEIGHT})});
    startButtonEngine->getComponent<Engine::AnimationComponent>()->addAnimation("hover", {Engine::Box<int>({START_BUTTON_X_HOVER, START_BUTTON_Y}, {START_BUTTON_WIDTH, START_BUTTON_HEIGHT})});
    startButtonEngine->getComponent<Engine::AnimationComponent>()->addAnimation("clicked", {Engine::Box<int>({START_BUTTON_X_CLICKED, START_BUTTON_Y}, {START_BUTTON_WIDTH, START_BUTTON_HEIGHT})});

    auto settingsButtonSprite = std::make_unique<SpriteSFML>(SETTINGS_BUTTON_PATH);
    auto settingsButtonEngine = new Engine::Button({SETTINGS_BUTTON_POSITION_X, SETTINGS_BUTTON_POSITION_Y}, std::move(settingsButtonSprite), &goToSettingsScene, std::shared_ptr<Engine::AScene>(this));
    settingsButtonEngine->getComponent<Engine::AnimationComponent>()->addAnimation("idle", {Engine::Box<int>({SETTINGS_BUTTON_X_IDLE, SETTINGS_BUTTON_Y}, {SETTINGS_BUTTON_WIDTH, SETTINGS_BUTTON_HEIGHT})});
    settingsButtonEngine->getComponent<Engine::AnimationComponent>()->addAnimation("hover", {Engine::Box<int>({SETTINGS_BUTTON_X_HOVER, SETTINGS_BUTTON_Y}, {SETTINGS_BUTTON_WIDTH, SETTINGS_BUTTON_HEIGHT})});
    settingsButtonEngine->getComponent<Engine::AnimationComponent>()->addAnimation("clicked", {Engine::Box<int>({SETTINGS_BUTTON_X_CLICKED, SETTINGS_BUTTON_Y}, {SETTINGS_BUTTON_WIDTH, SETTINGS_BUTTON_HEIGHT})});

    auto howToPlayButtonSprite = std::make_unique<SpriteSFML>(HOW_TO_PLAY_BUTTON_PATH);
    auto howToPlayButtonEngine = new Engine::Button({HOW_TO_PLAY_BUTTON_POSITION_X, HOW_TO_PLAY_BUTTON_POSITION_Y}, std::move(howToPlayButtonSprite), &goToHowToPlayScene, std::shared_ptr<Engine::AScene>(this));
    howToPlayButtonEngine->getComponent<Engine::AnimationComponent>()->addAnimation("idle", {Engine::Box<int>({HOW_TO_PLAY_BUTTON_X_IDLE, HOW_TO_PLAY_BUTTON_Y}, {HOW_TO_PLAY_BUTTON_WIDTH, HOW_TO_PLAY_BUTTON_HEIGHT})});
    howToPlayButtonEngine->getComponent<Engine::AnimationComponent>()->addAnimation("hover", {Engine::Box<int>({HOW_TO_PLAY_BUTTON_X_HOVER, HOW_TO_PLAY_BUTTON_Y}, {HOW_TO_PLAY_BUTTON_WIDTH, HOW_TO_PLAY_BUTTON_HEIGHT})});
    howToPlayButtonEngine->getComponent<Engine::AnimationComponent>()->addAnimation("clicked", {Engine::Box<int>({HOW_TO_PLAY_BUTTON_X_CLICKED, HOW_TO_PLAY_BUTTON_Y}, {HOW_TO_PLAY_BUTTON_WIDTH, HOW_TO_PLAY_BUTTON_HEIGHT})});

    auto quitButtonSprite = std::make_unique<SpriteSFML>(QUIT_BUTTON_PATH);
    auto quitButtonEngine = new Engine::Button({QUIT_BUTTON_POSITION_X, QUIT_BUTTON_POSITION_Y}, std::move(quitButtonSprite), &quitGame, std::shared_ptr<Engine::AScene>(this));
    quitButtonEngine->getComponent<Engine::AnimationComponent>()->addAnimation("idle", {Engine::Box<int>({QUIT_BUTTON_X_IDLE, QUIT_BUTTON_Y}, {QUIT_BUTTON_WIDTH, QUIT_BUTTON_HEIGHT})});
    quitButtonEngine->getComponent<Engine::AnimationComponent>()->addAnimation("hover", {Engine::Box<int>({QUIT_BUTTON_X_HOVER, QUIT_BUTTON_Y}, {QUIT_BUTTON_WIDTH, QUIT_BUTTON_HEIGHT})});
    quitButtonEngine->getComponent<Engine::AnimationComponent>()->addAnimation("clicked", {Engine::Box<int>({QUIT_BUTTON_X_CLICKED, QUIT_BUTTON_Y}, {QUIT_BUTTON_WIDTH, QUIT_BUTTON_HEIGHT})});


    /** test **/ // FIXME
    auto music = std::make_unique<MusicSFML>("../../client/assets/ogg/themes/menu_theme.ogg");
    auto musicE = new Engine::Music(std::move(music));

    /** ==== **/

    this->spawnEntity(std::shared_ptr<Engine::ParallaxSlide>(slideA));
    this->spawnEntity(std::shared_ptr<Engine::ParallaxSlide>(slideB));
    this->spawnEntity(std::shared_ptr<Engine::Button>(startButtonEngine));
    this->spawnEntity(std::shared_ptr<Engine::Button>(settingsButtonEngine));
    this->spawnEntity(std::shared_ptr<Engine::Button>(howToPlayButtonEngine));
    this->spawnEntity(std::shared_ptr<Engine::Button>(quitButtonEngine));
    this->spawnEntity(std::shared_ptr<Engine::Drawable>(rTypeLogoEngine));
    this->spawnEntity(std::shared_ptr<Engine::Music>(musicE));
}

void MainMenu::initSystems()
{
    auto draw = std::make_unique<Engine::DrawSystem>(this->_window);
    auto mouse = std::make_unique<Engine::MouseSystem>(this->_events);
    auto parallax = std::make_unique<Engine::ParallaxSystem>();
    auto animation = std::make_unique<Engine::AnimationSystem>();
    auto music = std::make_unique<Engine::MusicSystem>();

    this->_systems.push_back(std::move(draw));
    this->_systems.push_back(std::move(mouse));
    this->_systems.push_back(std::move(parallax));
    this->_systems.push_back(std::move(animation));
    this->_systems.push_back(std::move(music));
}

std::shared_ptr<Engine::AWindow> MainMenu::getWindow() const
{
    return _window;
}
