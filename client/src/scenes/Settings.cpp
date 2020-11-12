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
    auto fullscreenSelectorValue = settingsObject->getSelectorButtonsAndText();
    auto rect = fullscreenSelectorValue[SettingsSelectorSprite::FULLSCREEN_ENABLED].second->getComponent<Engine::SpriteComponent>()->getSprite()->getRect();
    fullscreenSelectorValue[SettingsSelectorSprite::FULLSCREEN_ENABLED].second->getComponent<Engine::SpriteComponent>()->getSprite()->setRect({Engine::Box<int>({(rect.x1 + ON_OFF_WIDTH) % ON_OFF_WIDTH_TOTAL, 0}, {ON_OFF_WIDTH, ON_OFF_HEIGHT})});

    //TODO implement change of fullscreen attribute
}

void changeWindowFramerateNext(std::shared_ptr<Engine::AScene> &settings)
{
    auto settingsObject = std::dynamic_pointer_cast<Settings>(settings);
    auto window = settingsObject->getWindow();
    auto actualFrameRate = window->getFrameRate();
    auto changeWindowSelectorValue = settingsObject->getSelectorButtonsAndText();

    if (actualFrameRate == 30) {
        window->setFrameRate(60);
        changeWindowSelectorValue[SettingsSelectorSprite::FRAMERATE].second->getComponent<Engine::SpriteComponent>()->getSprite()->setRect({Engine::Box<int>({FRAMERATE_VALUE_WIDTH, 0}, {FRAMERATE_VALUE_WIDTH, FRAMERATE_VALUE_HEIGHT})});
    } else if (actualFrameRate == 60) {
        window->setFrameRate(120);
        changeWindowSelectorValue[SettingsSelectorSprite::FRAMERATE].second->getComponent<Engine::SpriteComponent>()->getSprite()->setRect({Engine::Box<int>({FRAMERATE_VALUE_WIDTH * 2, 0}, {FRAMERATE_VALUE_WIDTH, FRAMERATE_VALUE_HEIGHT})});
    } else {
        window->setFrameRate(30);
        changeWindowSelectorValue[SettingsSelectorSprite::FRAMERATE].second->getComponent<Engine::SpriteComponent>()->getSprite()->setRect({Engine::Box<int>({0, 0}, {FRAMERATE_VALUE_WIDTH, FRAMERATE_VALUE_HEIGHT})});
    }

    //TODO fix parallax stopping when framerate is at 120 and find why there is a speed up when low framerate
}

void changeWindowFrameratePrev(std::shared_ptr<Engine::AScene> &settings)
{
    auto settingsObject = std::dynamic_pointer_cast<Settings>(settings);
    auto window = settingsObject->getWindow();
    auto actualFrameRate = window->getFrameRate();
    auto changeWindowSelectorValue = settingsObject->getSelectorButtonsAndText();

    if (actualFrameRate == 30) {
        window->setFrameRate(120);
        changeWindowSelectorValue[SettingsSelectorSprite::FRAMERATE].second->getComponent<Engine::SpriteComponent>()->getSprite()->setRect({Engine::Box<int>({FRAMERATE_VALUE_WIDTH * 2, 0}, {FRAMERATE_VALUE_WIDTH, FRAMERATE_VALUE_HEIGHT})});
    } else if (actualFrameRate == 60) {
        window->setFrameRate(30);
        changeWindowSelectorValue[SettingsSelectorSprite::FRAMERATE].second->getComponent<Engine::SpriteComponent>()->getSprite()->setRect({Engine::Box<int>({0, 0}, {FRAMERATE_VALUE_WIDTH, FRAMERATE_VALUE_HEIGHT})});
    } else {
        window->setFrameRate(60);
        changeWindowSelectorValue[SettingsSelectorSprite::FRAMERATE].second->getComponent<Engine::SpriteComponent>()->getSprite()->setRect({Engine::Box<int>({FRAMERATE_VALUE_WIDTH , 0}, {FRAMERATE_VALUE_WIDTH, FRAMERATE_VALUE_HEIGHT})});
    }

    //TODO fix parallax stopping when framerate is at 120 and find why there is a speed up when low framerate
}

void changeWindowVsync(std::shared_ptr<Engine::AScene> &settings)
{
    auto settingsObject = std::dynamic_pointer_cast<Settings>(settings);
    auto fullscreenSelectorValue = settingsObject->getSelectorButtonsAndText();
    auto rect = fullscreenSelectorValue[SettingsSelectorSprite::VSYNC_ENABLED].second->getComponent<Engine::SpriteComponent>()->getSprite()->getRect();
    auto window = settingsObject->getWindow();

    window->setVsync(!window->getVsync());
    fullscreenSelectorValue[SettingsSelectorSprite::VSYNC_ENABLED].second->getComponent<Engine::SpriteComponent>()->getSprite()->setRect({Engine::Box<int>({(rect.x1 + ON_OFF_WIDTH) % ON_OFF_WIDTH_TOTAL, 0}, {ON_OFF_WIDTH, ON_OFF_HEIGHT})});

}

void changeAudioEnableMusic(std::shared_ptr<Engine::AScene> &settings)
{
    auto settingsObject = std::dynamic_pointer_cast<Settings>(settings);
    auto fullscreenSelectorValue = settingsObject->getSelectorButtonsAndText();
    auto rect = fullscreenSelectorValue[SettingsSelectorSprite::MUSIC_ENABLED].second->getComponent<Engine::SpriteComponent>()->getSprite()->getRect();
    auto group = settingsObject->getGroupAccess();

    fullscreenSelectorValue[SettingsSelectorSprite::MUSIC_ENABLED].second->getComponent<Engine::SpriteComponent>()->getSprite()->setRect({Engine::Box<int>({(rect.x1 + ON_OFF_WIDTH) % ON_OFF_WIDTH_TOTAL, 0}, {ON_OFF_WIDTH, ON_OFF_HEIGHT})});
    if (Engine::Utils::isInMap(group, static_cast<int>(GroupId::MENU_MUSIC))) {
        group[GroupId::MENU_MUSIC]->getEntities()[0]->getComponent<Engine::MusicComponent>()->getMusic()->stop();
    }

    //TODO stop and reactivate the music properly
}

void changeAudioEnableSoundEffects(std::shared_ptr<Engine::AScene> &settings)
{
    auto settingsObject = std::dynamic_pointer_cast<Settings>(settings);
    auto fullscreenSelectorValue = settingsObject->getSelectorButtonsAndText();
    auto rect = fullscreenSelectorValue[SettingsSelectorSprite::SOUND_EFFECTS_ENABLED].second->getComponent<Engine::SpriteComponent>()->getSprite()->getRect();
    fullscreenSelectorValue[SettingsSelectorSprite::SOUND_EFFECTS_ENABLED].second->getComponent<Engine::SpriteComponent>()->getSprite()->setRect({Engine::Box<int>({(rect.x1 + ON_OFF_WIDTH) % ON_OFF_WIDTH_TOTAL, 0}, {ON_OFF_WIDTH, ON_OFF_HEIGHT})});

    //TODO stop and reactivate sound effects properly
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

void Settings::createSelector(Engine::Point<int> position,  const std::pair<void (*)(std::shared_ptr<Engine::AScene> &), void (*)(std::shared_ptr<Engine::AScene> &)> &callback, const std::string &path, std::unique_ptr<SpriteSFML> text)
{
    std::pair<std::shared_ptr<Engine::Button>, std::shared_ptr<Engine::Button>> fullScreenPairButton;
    std::pair<std::pair<std::shared_ptr<Engine::Button>, std::shared_ptr<Engine::Button>>, std::shared_ptr<Engine::Drawable>> fullScreenButtonAndText;
    auto fullScreenLeftButtonSprite = std::make_unique<SpriteSFML>(GO_BACK_BUTTON_PATH);
    fullScreenPairButton.first = std::make_shared<Engine::Button>(Engine::Point<int>{position.x, position.y}, Engine::Point<int>{GO_BACK_BUTTON_WIDTH, GO_BACK_BUTTON_HEIGHT}, std::move(fullScreenLeftButtonSprite), callback.first, std::shared_ptr<AScene>(this));
    fullScreenPairButton.first->getComponent<Engine::AnimationComponent>()->addAnimation(Engine::ButtonComponent::ButtonState::IDLE, {Engine::Box<int>({GO_BACK_BUTTON_X_IDLE, GO_BACK_BUTTON_Y}, {GO_BACK_BUTTON_WIDTH, GO_BACK_BUTTON_HEIGHT})});
    fullScreenPairButton.first->getComponent<Engine::AnimationComponent>()->addAnimation(Engine::ButtonComponent::HOVER, {Engine::Box<int>({GO_BACK_BUTTON_X_HOVER, GO_BACK_BUTTON_Y}, {GO_BACK_BUTTON_WIDTH, GO_BACK_BUTTON_HEIGHT})});
    fullScreenPairButton.first->getComponent<Engine::AnimationComponent>()->addAnimation(Engine::ButtonComponent::CLICKED, {Engine::Box<int>({GO_BACK_BUTTON_X_CLICKED, GO_BACK_BUTTON_Y}, {GO_BACK_BUTTON_WIDTH, GO_BACK_BUTTON_HEIGHT})});

    auto fullScreenRightButtonSprite = std::make_unique<SpriteSFML>(GO_NEXT_BUTTON_PATH);
    fullScreenPairButton.second = std::make_shared<Engine::Button>(Engine::Point<int>{position.x + 300, position.y}, Engine::Point<int>{GO_NEXT_BUTTON_WIDTH, GO_NEXT_BUTTON_HEIGHT}, std::move(fullScreenRightButtonSprite), callback.second, std::shared_ptr<AScene>(this));
    fullScreenPairButton.second->getComponent<Engine::AnimationComponent>()->addAnimation(Engine::ButtonComponent::ButtonState::IDLE, {Engine::Box<int>({GO_BACK_BUTTON_X_IDLE, GO_BACK_BUTTON_Y}, {GO_BACK_BUTTON_WIDTH, GO_BACK_BUTTON_HEIGHT})});
    fullScreenPairButton.second->getComponent<Engine::AnimationComponent>()->addAnimation(Engine::ButtonComponent::HOVER, {Engine::Box<int>({GO_BACK_BUTTON_X_HOVER, GO_BACK_BUTTON_Y}, {GO_BACK_BUTTON_WIDTH, GO_BACK_BUTTON_HEIGHT})});
    fullScreenPairButton.second->getComponent<Engine::AnimationComponent>()->addAnimation(Engine::ButtonComponent::CLICKED, {Engine::Box<int>({GO_BACK_BUTTON_X_CLICKED, GO_BACK_BUTTON_Y}, {GO_BACK_BUTTON_WIDTH, GO_BACK_BUTTON_HEIGHT})});

    auto onOffFTextEngine = std::make_shared<Engine::Drawable>(Engine::Point<int>{position.x + 120, position.y + 7}, std::move(text));

    fullScreenButtonAndText.first = fullScreenPairButton;
    fullScreenButtonAndText.second = onOffFTextEngine;
    _selectorButtonsAndText.push_back(fullScreenButtonAndText);
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

    auto onOffFTextWindowEnableFullscreen = std::make_unique<SpriteSFML>(ON_OFF_PATH);
    onOffFTextWindowEnableFullscreen ->setRect({Engine::Box<int>({0, 0}, {ON_OFF_WIDTH, ON_OFF_HEIGHT})});
    createSelector({static_cast<int>(LEFT_BUTTON_FULLSCREEN_POSITION_X),static_cast<int>(RIGHT_BUTTON_FULLSCREEN_POSITION_Y)}, {changeWindowEnableFullscreen, changeWindowEnableFullscreen}, ON_OFF_PATH, std::move(onOffFTextWindowEnableFullscreen ));
    auto framerateTextNumber = std::make_unique<SpriteSFML>(FRAMERATE_VALUE_PATH);
    framerateTextNumber->setRect({Engine::Box<int>({0, 0}, {FRAMERATE_VALUE_WIDTH, FRAMERATE_VALUE_HEIGHT})});
    createSelector({static_cast<int>(LEFT_BUTTON_FRAMERATE_POSITION_X),static_cast<int>(RIGHT_BUTTON_FRAMERATE_POSITION_Y)}, {changeWindowFrameratePrev, changeWindowFramerateNext}, FRAMERATE_VALUE_PATH, std::move(framerateTextNumber));
    auto onOffFTextWindowVSync = std::make_unique<SpriteSFML>(ON_OFF_PATH);
    onOffFTextWindowVSync->setRect({Engine::Box<int>({0, 0}, {ON_OFF_WIDTH, ON_OFF_HEIGHT})});
    createSelector({static_cast<int>(LEFT_BUTTON_VSYNC_POSITION_X),static_cast<int>(RIGHT_BUTTON_VSYNC_POSITION_Y)}, {changeWindowVsync, changeWindowVsync}, ON_OFF_PATH, std::move(onOffFTextWindowVSync));
    auto onOffFTextMusicEnabled = std::make_unique<SpriteSFML>(ON_OFF_PATH);
    onOffFTextMusicEnabled->setRect({Engine::Box<int>({0, 0}, {ON_OFF_WIDTH, ON_OFF_HEIGHT})});
    createSelector({static_cast<int>(LEFT_BUTTON_MUSIC_POSITION_X),static_cast<int>(RIGHT_BUTTON_MUSIC_POSITION_Y)}, {changeAudioEnableMusic, changeAudioEnableMusic}, ON_OFF_PATH, std::move(onOffFTextMusicEnabled));
    auto onOffFTextSoundEffectEnabled = std::make_unique<SpriteSFML>(ON_OFF_PATH);
    onOffFTextSoundEffectEnabled->setRect({Engine::Box<int>({0, 0}, {ON_OFF_WIDTH, ON_OFF_HEIGHT})});
    createSelector({static_cast<int>(LEFT_BUTTON_SOUND_EFFECTS_POSITION_X),static_cast<int>(RIGHT_BUTTON_SOUND_EFFECTS_POSITION_Y)} , {changeAudioEnableSoundEffects, changeAudioEnableSoundEffects}, ON_OFF_PATH, std::move(onOffFTextSoundEffectEnabled));

    this->spawnEntity(enableFullscreenEngine);
    this->spawnEntity(framerateEngine);
    this->spawnEntity(vsyncEngine);
    this->spawnEntity(musicEngine);
    this->spawnEntity(soundEffectsEngine);
    this->spawnEntity(goBackButtonEngine);
    for (auto &buttonEngine : _selectorButtonsAndText) {
        this->spawnEntity(buttonEngine.first.first);
        this->spawnEntity(buttonEngine.first.second);
        this->spawnEntity(buttonEngine.second);
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

std::vector<std::pair<std::pair<std::shared_ptr<Engine::Entity>, std::shared_ptr<Engine::Entity>>, std::shared_ptr<Engine::Entity>>> Settings::getSelectorButtonsAndText() const
{
    return _selectorButtonsAndText;
}