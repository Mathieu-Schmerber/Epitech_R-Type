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
#include "scenes/GroupId.hpp"
#include "tools/Utils.hpp"
#include "components/MusicComponent.hpp"

void changeWindowEnableFullscreen(std::shared_ptr<Engine::AScene> &settings)
{

}

void changeWindowFramerate(std::shared_ptr<Engine::AScene> &settings)
{

}

void changeWindowVsync(std::shared_ptr<Engine::AScene> &settings)
{
    auto settingsObject = std::dynamic_pointer_cast<Settings>(settings);
    auto window = settingsObject->getWindow();

    //if (window->getSize())window->setFrameRate();
}

void changeAudioEnableMusic(std::shared_ptr<Engine::AScene> &settings)
{
    auto group = std::dynamic_pointer_cast<Settings>(settings)->getGroupAccess();

    if (Engine::Utils::isInMap(group, static_cast<int>(GroupId::MENU_MUSIC))) {

        group[GroupId::MENU_MUSIC]->getEntities()[0]->getComponent<Engine::MusicComponent>()->getMusic()->pause();
    }
}

void changeAudioEnableSoundEffects(std::shared_ptr<Engine::AScene> &settings)
{

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

void Settings::createSelector(Engine::Point<int> leftPosition, void (*callback)(std::shared_ptr<Engine::AScene> &))
{
    std::pair<std::shared_ptr<Engine::Button>, std::shared_ptr<Engine::Button>> fullScreenPairButton;
    auto fullScreenLeftButtonSprite = std::make_unique<SpriteSFML>(GO_BACK_BUTTON_PATH);
    fullScreenPairButton.first = std::make_shared<Engine::Button>(Engine::Point<int>{leftPosition.x, leftPosition.y}, std::move(fullScreenLeftButtonSprite), callback, std::shared_ptr<AScene>(this));
    fullScreenPairButton.first->getComponent<Engine::AnimationComponent>()->addAnimation(Engine::IDLE, {Engine::Box<int>({GO_BACK_BUTTON_X_IDLE, GO_BACK_BUTTON_Y}, {GO_BACK_BUTTON_WIDTH, GO_BACK_BUTTON_HEIGHT})});
    fullScreenPairButton.first->getComponent<Engine::AnimationComponent>()->addAnimation(Engine::HOVER, {Engine::Box<int>({GO_BACK_BUTTON_X_HOVER, GO_BACK_BUTTON_Y}, {GO_BACK_BUTTON_WIDTH, GO_BACK_BUTTON_HEIGHT})});
    fullScreenPairButton.first->getComponent<Engine::AnimationComponent>()->addAnimation(Engine::CLICKED, {Engine::Box<int>({GO_BACK_BUTTON_X_CLICKED, GO_BACK_BUTTON_Y}, {GO_BACK_BUTTON_WIDTH, GO_BACK_BUTTON_HEIGHT})});

    auto fullScreenRightButtonSprite = std::make_unique<SpriteSFML>(GO_NEXT_BUTTON_PATH);
    fullScreenPairButton.second = std::make_shared<Engine::Button>(Engine::Point<int>{leftPosition.x + 300, leftPosition.y}, std::move(fullScreenRightButtonSprite), callback, std::shared_ptr<AScene>(this));
    fullScreenPairButton.second->getComponent<Engine::AnimationComponent>()->addAnimation(Engine::IDLE, {Engine::Box<int>({GO_BACK_BUTTON_X_IDLE, GO_BACK_BUTTON_Y}, {GO_BACK_BUTTON_WIDTH, GO_BACK_BUTTON_HEIGHT})});
    fullScreenPairButton.second->getComponent<Engine::AnimationComponent>()->addAnimation(Engine::HOVER, {Engine::Box<int>({GO_BACK_BUTTON_X_HOVER, GO_BACK_BUTTON_Y}, {GO_BACK_BUTTON_WIDTH, GO_BACK_BUTTON_HEIGHT})});
    fullScreenPairButton.second->getComponent<Engine::AnimationComponent>()->addAnimation(Engine::CLICKED, {Engine::Box<int>({GO_BACK_BUTTON_X_CLICKED, GO_BACK_BUTTON_Y}, {GO_BACK_BUTTON_WIDTH, GO_BACK_BUTTON_HEIGHT})});

    _selectorButtons.push_back(fullScreenPairButton);
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

    createSelector({static_cast<int>(LEFT_BUTTON_FULLSCREEN_POSITION_X),static_cast<int>(RIGHT_BUTTON_FULLSCREEN_POSITION_Y)}, changeWindowEnableFullscreen);
    createSelector({static_cast<int>(LEFT_BUTTON_FRAMERATE_POSITION_X),static_cast<int>(RIGHT_BUTTON_FRAMERATE_POSITION_Y)} ,changeWindowFramerate);
    createSelector({static_cast<int>(LEFT_BUTTON_VSYNC_POSITION_X),static_cast<int>(RIGHT_BUTTON_VSYNC_POSITION_Y)} ,changeWindowVsync);
    createSelector({static_cast<int>(LEFT_BUTTON_MUSIC_POSITION_X),static_cast<int>(RIGHT_BUTTON_MUSIC_POSITION_Y)} ,changeAudioEnableMusic);
    createSelector({static_cast<int>(LEFT_BUTTON_SOUND_EFFECTS_POSITION_X),static_cast<int>(RIGHT_BUTTON_SOUND_EFFECTS_POSITION_Y)} ,changeAudioEnableSoundEffects);

    this->spawnEntity(std::shared_ptr<Engine::Drawable>(enableFullscreenEngine));
    this->spawnEntity(std::shared_ptr<Engine::Drawable>(framerateEngine));
    this->spawnEntity(std::shared_ptr<Engine::Drawable>(vsyncEngine));
    this->spawnEntity(std::shared_ptr<Engine::Drawable>(musicEngine));
    this->spawnEntity(std::shared_ptr<Engine::Drawable>(soundEffectsEngine));
    this->spawnEntity(std::shared_ptr<Engine::Button>(goBackButtonEngine));
    for (auto &buttonEngine : _selectorButtons) {
        this->spawnEntity(buttonEngine.first);
        this->spawnEntity(buttonEngine.second);
    }
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

std::shared_ptr<Engine::AWindow> Settings::getWindow() const
{
    return _window;
}

void Settings::setFrameRate(int newFrameRate)
{
    _frameRate = newFrameRate;
}
