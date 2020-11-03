//
// Created by mathi on 02/11/2020.
//

#include <sfml/SpriteSfml.hpp>
#include "sceneManagement/SceneManager.hpp"
#include "systems/DrawSystem.hpp"
#include "systems/MouseSystem.hpp"
#include "systems/ParallaxSystem.hpp"
#include "scenes/Settings.hpp"
#include "entities/ParallaxSlide.hpp"
#include "entities/Drawable.hpp"
#include "entities/Button.hpp"
#include "systems/AnimationSystem.hpp"
#include "enumerations/ButtonState.hpp"

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
    auto goBackButtonEngine = new Engine::Button({GO_BACK_BUTTON_POSITION_X, GO_BACK_BUTTON_POSITION_Y}, std::move(goBackButtonSprite), &goToMenuScene, std::shared_ptr<Engine::AScene>(this));
    goBackButtonEngine->getComponent<Engine::AnimationComponent>()->addAnimation(Engine::ButtonState::IDLE, {Engine::Box<int>({GO_BACK_BUTTON_X_IDLE, GO_BACK_BUTTON_Y}, {GO_BACK_BUTTON_WIDTH, GO_BACK_BUTTON_HEIGHT})});
    goBackButtonEngine->getComponent<Engine::AnimationComponent>()->addAnimation(Engine::ButtonState::HOVER, {Engine::Box<int>({GO_BACK_BUTTON_X_HOVER, GO_BACK_BUTTON_Y}, {GO_BACK_BUTTON_WIDTH, GO_BACK_BUTTON_HEIGHT})});
    goBackButtonEngine->getComponent<Engine::AnimationComponent>()->addAnimation(Engine::ButtonState::CLICKED, {Engine::Box<int>({GO_BACK_BUTTON_X_CLICKED, GO_BACK_BUTTON_Y}, {GO_BACK_BUTTON_WIDTH, GO_BACK_BUTTON_HEIGHT})});

    auto enableFullscreenText = std::make_unique<SpriteSFML>(FULLSCREEN_TEXT_PATH);
    auto enableFullscreenEngine = new Engine::Drawable({FULLSCREEN_TEXT_POSITION_X, FULLSCREEN_TEXT_POSITION_Y}, std::move(enableFullscreenText));

    auto framerateText = std::make_unique<SpriteSFML>(FRAMERATE_TEXT_PATH);
    auto framerateEngine = new Engine::Drawable({FRAMERATE_TEXT_POSITION_X, FRAMERATE_TEXT_POSITION_Y}, std::move(framerateText));

    auto vsyncText = std::make_unique<SpriteSFML>(VSYNC_TEXT_PATH);
    auto vsyncEngine = new Engine::Drawable({VSYNC_TEXT_POSITION_X, VSYNC_TEXT_POSITION_Y}, std::move(vsyncText));

    auto musicText = std::make_unique<SpriteSFML>(MUSIC_TEXT_PATH);
    auto musicEngine = new Engine::Drawable({MUSIC_TEXT_POSITION_X, MUSIC_TEXT_POSITION_Y}, std::move(musicText));

    auto soundEffectsText = std::make_unique<SpriteSFML>(SOUND_EFFECTS_TEXT_PATH);
    auto soundEffectsEngine = new Engine::Drawable({SOUND_EFFECTS_TEXT_POSITION_X, SOUND_EFFECTS_TEXT_POSITION_Y}, std::move(soundEffectsText));

    this->spawnEntity(std::shared_ptr<Engine::Drawable>(enableFullscreenEngine));
    this->spawnEntity(std::shared_ptr<Engine::Drawable>(framerateEngine));
    this->spawnEntity(std::shared_ptr<Engine::Drawable>(vsyncEngine));
    this->spawnEntity(std::shared_ptr<Engine::Drawable>(musicEngine));
    this->spawnEntity(std::shared_ptr<Engine::Drawable>(soundEffectsEngine));
    this->spawnEntity(std::shared_ptr<Engine::Button>(goBackButtonEngine));
}

void Settings::initSystems()
{
    auto draw = std::make_unique<Engine::DrawSystem>(this->_window);
    auto mouse = std::make_unique<Engine::MouseSystem>(this->_events);
    auto parallax = std::make_unique<Engine::ParallaxSystem>();
    auto animation = std::make_unique<Engine::AnimationSystem>();

    this->_systems.push_back(std::move(draw));
    this->_systems.push_back(std::move(mouse));
    this->_systems.push_back(std::move(animation));
    this->_systems.push_back(std::move(parallax));
}