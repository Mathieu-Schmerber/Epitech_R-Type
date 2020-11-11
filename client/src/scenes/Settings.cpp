//
// Created by mathi on 02/11/2020.
//

#include "sceneManagement/SceneManager.hpp"
#include "systems/DrawSystem.hpp"
#include "systems/MouseSystem.hpp"
#include "systems/ButtonSystem.hpp"
#include "systems/MoveSystem.hpp"
#include "systems/ParallaxSystem.hpp"
#include "systems/WindowResizeSystem.hpp"
#include "scenes/Settings.hpp"
#include "systems/AnimationSystem.hpp"
#include "scenes/GroupId.hpp"
#include "components/MusicComponent.hpp"

void changeWindowEnableFullscreen(std::shared_ptr<Engine::AScene> &settings)
{
    auto settingsObject = std::dynamic_pointer_cast<Settings>(settings);

    for (auto &e : settingsObject->getEntities()) {
        auto sprite = e->getComponent<Engine::SpriteComponent>();
        if (sprite)
            std::cout << sprite->getSprite()->getRect().x1;
    }
}

void goToMenuScene(std::shared_ptr<Engine::AScene> &settings)
{
    Engine::SceneRequest request(Engine::QueryType::SWITCH_SCENE, SceneType::MAIN_MENU);

    settings->pushRequest(request);
}

Settings::Settings(std::shared_ptr<Engine::AWindow> &window, std::shared_ptr<Engine::AEvents> &events)
        : _window(window), _events(events), Engine::AScene(SceneType::SETTINGS)
{
    this->initSystems();
    this->initEntities();
}

void Settings::initEntities()
{
    auto goBackButtonSprite = std::make_unique<SpriteSFML>(GO_BACK_BUTTON_PATH);
    std::shared_ptr<Engine::Entity> goBackButtonEngine = std::make_shared<Engine::Button>(Engine::Point<int>{GO_BACK_BUTTON_POSITION_X, GO_BACK_BUTTON_POSITION_Y}, Engine::Point<int>{GO_BACK_BUTTON_WIDTH, GO_BACK_BUTTON_HEIGHT}, std::move(goBackButtonSprite), &goToMenuScene, std::shared_ptr<Engine::AScene>(this));
    goBackButtonEngine->getComponent<Engine::AnimationComponent>()->addAnimation(Engine::ButtonComponent::ButtonState::IDLE, {Engine::Box<int>({GO_BACK_BUTTON_X_IDLE, GO_BACK_BUTTON_Y}, {GO_BACK_BUTTON_WIDTH, GO_BACK_BUTTON_HEIGHT})});
    goBackButtonEngine->getComponent<Engine::AnimationComponent>()->addAnimation(Engine::ButtonComponent::ButtonState::HOVER, {Engine::Box<int>({GO_BACK_BUTTON_X_HOVER, GO_BACK_BUTTON_Y}, {GO_BACK_BUTTON_WIDTH, GO_BACK_BUTTON_HEIGHT})});
    goBackButtonEngine->getComponent<Engine::AnimationComponent>()->addAnimation(Engine::ButtonComponent::ButtonState::CLICKED, {Engine::Box<int>({GO_BACK_BUTTON_X_CLICKED, GO_BACK_BUTTON_Y}, {GO_BACK_BUTTON_WIDTH, GO_BACK_BUTTON_HEIGHT})});

    auto enableFullscreenText = std::make_unique<SpriteSFML>(FULLSCREEN_TEXT_PATH);
    std::shared_ptr<Engine::Entity> enableFullscreenEngine = std::make_shared<Engine::Drawable>(Engine::Point<int>{FULLSCREEN_TEXT_POSITION_X, FULLSCREEN_TEXT_POSITION_Y}, std::move(enableFullscreenText));

    auto framerateText = std::make_unique<SpriteSFML>(FRAMERATE_TEXT_PATH);
    std::shared_ptr<Engine::Entity> framerateEngine = std::make_shared<Engine::Drawable>(Engine::Point<int>{FRAMERATE_TEXT_POSITION_X, FRAMERATE_TEXT_POSITION_Y}, std::move(framerateText));

    auto vsyncText = std::make_unique<SpriteSFML>(VSYNC_TEXT_PATH);
    std::shared_ptr<Engine::Entity> vsyncEngine = std::make_shared<Engine::Drawable>(Engine::Point<int>{VSYNC_TEXT_POSITION_X, VSYNC_TEXT_POSITION_Y}, std::move(vsyncText));

    auto musicText = std::make_unique<SpriteSFML>(MUSIC_TEXT_PATH);
    std::shared_ptr<Engine::Entity> musicEngine = std::make_shared<Engine::Drawable>(Engine::Point<int>{MUSIC_TEXT_POSITION_X, MUSIC_TEXT_POSITION_Y}, std::move(musicText));

    auto soundEffectsText = std::make_unique<SpriteSFML>(SOUND_EFFECTS_TEXT_PATH);
    std::shared_ptr<Engine::Entity> soundEffectsEngine = std::make_shared<Engine::Drawable>(Engine::Point<int>{SOUND_EFFECTS_TEXT_POSITION_X, SOUND_EFFECTS_TEXT_POSITION_Y}, std::move(soundEffectsText));

    auto buttonSprite = std::make_unique<SpriteSFML>(GO_NEXT_BUTTON_PATH);
    std::shared_ptr<Engine::Entity> button = std::make_shared<Engine::Button>(Engine::Point<int>{0 + 300,0},
        Engine::Point<int>{GO_NEXT_BUTTON_WIDTH, GO_NEXT_BUTTON_HEIGHT},
        std::move(buttonSprite), changeWindowEnableFullscreen, std::shared_ptr<AScene>(this));
    _entities.emplace_back(button);

    this->spawnEntity(enableFullscreenEngine);
    this->spawnEntity(framerateEngine);
    this->spawnEntity(vsyncEngine);
    this->spawnEntity(musicEngine);
    this->spawnEntity(soundEffectsEngine);
    this->spawnEntity(goBackButtonEngine);
    for (auto &e: _entities) {
        this->spawnEntity(e);
    }
}

void Settings::initSystems()
{
    auto draw = std::make_unique<Engine::DrawSystem>(this->_window);
    auto mouse = std::make_unique<Engine::MouseSystem>(this->_events);
    auto btn = std::make_unique<Engine::ButtonSystem>();
    auto parallax = std::make_unique<Engine::ParallaxSystem>();
    auto move = std::make_unique<Engine::MoveSystem>();
    auto animation = std::make_unique<Engine::AnimationSystem>();
    auto window = std::make_unique<Engine::WindowResizeSystem>(this->_window);

    this->_systems.push_back(std::move(draw));
    this->_systems.push_back(std::move(mouse));
    this->_systems.push_back(std::move(btn));
    this->_systems.push_back(std::move(animation));
    this->_systems.push_back(std::move(parallax));
    this->_systems.push_back(std::move(move));
    this->_systems.push_back(std::move(window));
}

std::shared_ptr<Engine::AWindow> Settings::getWindow() const
{
    return _window;
}