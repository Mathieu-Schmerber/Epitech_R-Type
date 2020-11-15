//
// Created by mathi on 02/11/2020.
//

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

#define INT(x) static_cast<int>(x)
#define FLOAT(x) static_cast<double>(x)

/*!
 * \brief changeWindowEnableFullscreen button callback
 * \param settings actual scene
 *
 * This callback permit to change window fullscreen property
*/

void changeWindowEnableFullscreen(std::shared_ptr<Engine::AScene> &settings)
{
    auto settingsObject = std::dynamic_pointer_cast<Settings>(settings);
    auto fullscreenSelectorValue = settingsObject->getSettingsEntities();
    auto rect = fullscreenSelectorValue[SettingsSelectorSprite::FULLSCREEN_ENABLED]->getComponent<Engine::SpriteComponent>()->getSprite()->getRect();
    fullscreenSelectorValue[SettingsSelectorSprite::FULLSCREEN_ENABLED]->getComponent<Engine::SpriteComponent>()->getSprite()->setRect({Engine::Box<double>({FLOAT(INT(rect.x1 + ON_OFF_WIDTH) % ON_OFF_WIDTH_TOTAL), 0}, {ON_OFF_WIDTH, ON_OFF_HEIGHT})});

    //TODO implement change of fullscreen attribute
}

/*!
 * \brief changeWindowFramerateNext button callback
 * \param settings actual scene
 *
 * TThis callback permit to change window framerate property to the next one (30, 60 or 120)
*/

void changeWindowFramerateNext(std::shared_ptr<Engine::AScene> &settings)
{
    auto settingsObject = std::dynamic_pointer_cast<Settings>(settings);
    auto window = settingsObject->getWindow();
    auto actualFrameRate = window->getFrameRate();
    auto changeWindowSelectorValue = settingsObject->getSettingsEntities();

    if (actualFrameRate == 30) {
        window->setFrameRate(60);
        changeWindowSelectorValue[SettingsSelectorSprite::FRAMERATE]->getComponent<Engine::SpriteComponent>()->getSprite()->setRect({Engine::Box<double>({FRAMERATE_VALUE_WIDTH, 0}, {FRAMERATE_VALUE_WIDTH, FRAMERATE_VALUE_HEIGHT})});
    } else if (actualFrameRate == 60) {
        window->setFrameRate(120);
        changeWindowSelectorValue[SettingsSelectorSprite::FRAMERATE]->getComponent<Engine::SpriteComponent>()->getSprite()->setRect({Engine::Box<double>({FRAMERATE_VALUE_WIDTH * 2, 0}, {FRAMERATE_VALUE_WIDTH, FRAMERATE_VALUE_HEIGHT})});
    } else {
        window->setFrameRate(30);
        changeWindowSelectorValue[SettingsSelectorSprite::FRAMERATE]->getComponent<Engine::SpriteComponent>()->getSprite()->setRect({Engine::Box<double>({0, 0}, {FRAMERATE_VALUE_WIDTH, FRAMERATE_VALUE_HEIGHT})});
    }

    //TODO fix parallax stopping when framerate is at 120 and find why there is a speed up when low framerate
}

/*!
 * \brief changeWindowFrameratePrev button callback
 * \param settings actual scene
 *
 * This callback permit to change window framerate property to the previous one (30, 60 or 120)
*/

void changeWindowFrameratePrev(std::shared_ptr<Engine::AScene> &settings)
{
    auto settingsObject = std::dynamic_pointer_cast<Settings>(settings);
    auto window = settingsObject->getWindow();
    auto actualFrameRate = window->getFrameRate();
    auto changeWindowSelectorValue = settingsObject->getSettingsEntities();

    if (actualFrameRate == 30) {
        window->setFrameRate(120);
        changeWindowSelectorValue[SettingsSelectorSprite::FRAMERATE]->getComponent<Engine::SpriteComponent>()->getSprite()->setRect({Engine::Box<double>({FRAMERATE_VALUE_WIDTH * 2, 0}, {FRAMERATE_VALUE_WIDTH, FRAMERATE_VALUE_HEIGHT})});
    } else if (actualFrameRate == 60) {
        window->setFrameRate(30);
        changeWindowSelectorValue[SettingsSelectorSprite::FRAMERATE]->getComponent<Engine::SpriteComponent>()->getSprite()->setRect({Engine::Box<double>({0, 0}, {FRAMERATE_VALUE_WIDTH, FRAMERATE_VALUE_HEIGHT})});
    } else {
        window->setFrameRate(60);
        changeWindowSelectorValue[SettingsSelectorSprite::FRAMERATE]->getComponent<Engine::SpriteComponent>()->getSprite()->setRect({Engine::Box<double>({FRAMERATE_VALUE_WIDTH , 0}, {FRAMERATE_VALUE_WIDTH, FRAMERATE_VALUE_HEIGHT})});
    }

    //TODO fix parallax stopping when framerate is at 120 and find why there is a speed up when low framerate
}

/*!
 * \brief changeWindowVsync button callback
 * \param settings actual scene
 *
 * This callback permit to change window Vertical Sync property to true or false
*/

void changeWindowVsync(std::shared_ptr<Engine::AScene> &settings)
{
    auto settingsObject = std::dynamic_pointer_cast<Settings>(settings);
    auto fullscreenSelectorValue = settingsObject->getSettingsEntities();
    auto rect = fullscreenSelectorValue[SettingsSelectorSprite::VSYNC_ENABLED]->getComponent<Engine::SpriteComponent>()->getSprite()->getRect();
    auto window = settingsObject->getWindow();

    window->setVsync(!window->getVsync());
    fullscreenSelectorValue[SettingsSelectorSprite::VSYNC_ENABLED]->getComponent<Engine::SpriteComponent>()->getSprite()->setRect({Engine::Box<double>({FLOAT(INT(rect.x1 + ON_OFF_WIDTH) % ON_OFF_WIDTH_TOTAL), 0}, {ON_OFF_WIDTH, ON_OFF_HEIGHT})});
}

/*!
 * \brief changeAudioEnableMusic button callback
 * \param settings actual scene
 *
 * This callback permit to activate or disable the music
*/

void changeAudioEnableMusic(std::shared_ptr<Engine::AScene> &settings)
{
    auto settingsObject = std::dynamic_pointer_cast<Settings>(settings);
    auto fullscreenSelectorValue = settingsObject->getSettingsEntities();
    auto rect = fullscreenSelectorValue[SettingsSelectorSprite::MUSIC_ENABLED]->getComponent<Engine::SpriteComponent>()->getSprite()->getRect();
    auto group = settingsObject->getGroupAccess();
    auto window = settingsObject->getWindow();

    fullscreenSelectorValue[SettingsSelectorSprite::MUSIC_ENABLED]->getComponent<Engine::SpriteComponent>()->getSprite()->setRect({Engine::Box<double>({static_cast<double>(static_cast<int>((rect.x1 + ON_OFF_WIDTH)) % ON_OFF_WIDTH_TOTAL), 0}, {ON_OFF_WIDTH, ON_OFF_HEIGHT})});
    if (Engine::Utils::isInMap(group, static_cast<int>(GroupId::MENU_MUSIC))) {
        auto &music = group[GroupId::MENU_MUSIC]->getEntities()[0]->getComponent<Engine::MusicComponent>()->getMusic();
        if (music->isStopped()) {
            music->play(100);
            window->setMusic(true);
        } else {
            music->stop();
            window->setMusic(false);
        }
    }

    //TODO stop and reactivate the music properly
}

/*!
 * \brief changeAudioEnableSoundEffects button callback
 * \param settings actual scene
 *
 * This callback permit to activate or disable the sound effects
*/

void changeAudioEnableSoundEffects(std::shared_ptr<Engine::AScene> &settings)
{
    auto settingsObject = std::dynamic_pointer_cast<Settings>(settings);
    auto fullscreenSelectorValue = settingsObject->getSettingsEntities();
    auto rect = fullscreenSelectorValue[SettingsSelectorSprite::SOUND_EFFECTS_ENABLED]->getComponent<Engine::SpriteComponent>()->getSprite()->getRect();
    auto window = settingsObject->getWindow();

    fullscreenSelectorValue[SettingsSelectorSprite::SOUND_EFFECTS_ENABLED]->getComponent<Engine::SpriteComponent>()->getSprite()->setRect({Engine::Box<double>({FLOAT(INT(rect.x1 + ON_OFF_WIDTH) % ON_OFF_WIDTH_TOTAL), 0}, {ON_OFF_WIDTH, ON_OFF_HEIGHT})});
    window->setSound(!window->hasSound());
}

/*!
 * \brief goToMenuScene button callback
 * \param settings actual scene
 *
 * This callback permit to go to the "MainMenu" scene
*/

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

void Settings::createSelector(Engine::Point<double> position,  const std::pair<void (*)(std::shared_ptr<Engine::AScene> &), void (*)(std::shared_ptr<Engine::AScene> &)> &callback, const std::string &path, std::unique_ptr<SpriteSFML> text)
{
    auto fullScreenLeftButtonSprite = std::make_unique<SpriteSFML>(GO_BACK_BUTTON_PATH);
    std::shared_ptr<Engine::Entity> leftButton = std::make_shared<Engine::Button>(Engine::Point<double>{position.x, position.y}, Engine::Point<double>{GO_BACK_BUTTON_WIDTH, GO_BACK_BUTTON_HEIGHT}, std::move(fullScreenLeftButtonSprite), callback.first, std::shared_ptr<AScene>(this));
    leftButton->getComponent<Engine::AnimationComponent>()->addAnimation(Engine::ButtonComponent::ButtonState::IDLE, {Engine::Box<double>({GO_BACK_BUTTON_X_IDLE, GO_BACK_BUTTON_Y}, {GO_BACK_BUTTON_WIDTH, GO_BACK_BUTTON_HEIGHT})});
    leftButton->getComponent<Engine::AnimationComponent>()->addAnimation(Engine::ButtonComponent::HOVER, {Engine::Box<double>({GO_BACK_BUTTON_X_HOVER, GO_BACK_BUTTON_Y}, {GO_BACK_BUTTON_WIDTH, GO_BACK_BUTTON_HEIGHT})});
    leftButton->getComponent<Engine::AnimationComponent>()->addAnimation(Engine::ButtonComponent::CLICKED, {Engine::Box<double>({GO_BACK_BUTTON_X_CLICKED, GO_BACK_BUTTON_Y}, {GO_BACK_BUTTON_WIDTH, GO_BACK_BUTTON_HEIGHT})});

    auto fullScreenRightButtonSprite = std::make_unique<SpriteSFML>(GO_NEXT_BUTTON_PATH);
    std::shared_ptr<Engine::Entity> rightButton = std::make_shared<Engine::Button>(Engine::Point<double>{position.x + 300, position.y}, Engine::Point<double>{GO_NEXT_BUTTON_WIDTH, GO_NEXT_BUTTON_HEIGHT}, std::move(fullScreenRightButtonSprite), callback.second, std::shared_ptr<AScene>(this));
    rightButton->getComponent<Engine::AnimationComponent>()->addAnimation(Engine::ButtonComponent::ButtonState::IDLE, {Engine::Box<double>({GO_NEXT_BUTTON_X_IDLE, GO_BACK_BUTTON_Y}, {GO_NEXT_BUTTON_WIDTH, GO_NEXT_BUTTON_HEIGHT})});
    rightButton->getComponent<Engine::AnimationComponent>()->addAnimation(Engine::ButtonComponent::HOVER, {Engine::Box<double>({GO_NEXT_BUTTON_X_HOVER, GO_NEXT_BUTTON_Y}, {GO_NEXT_BUTTON_WIDTH, GO_NEXT_BUTTON_HEIGHT})});
    rightButton->getComponent<Engine::AnimationComponent>()->addAnimation(Engine::ButtonComponent::CLICKED, {Engine::Box<double>({GO_NEXT_BUTTON_X_CLICKED, GO_NEXT_BUTTON_Y}, {GO_NEXT_BUTTON_WIDTH, GO_NEXT_BUTTON_HEIGHT})});

    std::shared_ptr<Engine::Entity> textSprite = std::make_shared<Engine::Drawable>(Engine::Point<double>{position.x + 120, position.y + 7}, std::move(text));

    _settingsEntities.push_back(textSprite);

    this->spawnEntity(leftButton);
    this->spawnEntity(textSprite);
    this->spawnEntity(rightButton);
}

void Settings::initEntities()
{
    auto goBackButtonSprite = std::make_unique<SpriteSFML>(GO_BACK_BUTTON_PATH);
    std::shared_ptr<Engine::Entity> goBackButtonEngine = std::make_shared<Engine::Button>(Engine::Point<double>{GO_BACK_BUTTON_POSITION_X, GO_BACK_BUTTON_POSITION_Y}, Engine::Point<double>{GO_BACK_BUTTON_WIDTH, GO_BACK_BUTTON_HEIGHT}, std::move(goBackButtonSprite), &goToMenuScene, std::shared_ptr<Engine::AScene>(this));
    goBackButtonEngine->getComponent<Engine::AnimationComponent>()->addAnimation(Engine::ButtonComponent::ButtonState::IDLE, {Engine::Box<double>({GO_BACK_BUTTON_X_IDLE, GO_BACK_BUTTON_Y}, {GO_BACK_BUTTON_WIDTH, GO_BACK_BUTTON_HEIGHT})});
    goBackButtonEngine->getComponent<Engine::AnimationComponent>()->addAnimation(Engine::ButtonComponent::ButtonState::HOVER, {Engine::Box<double>({GO_BACK_BUTTON_X_HOVER, GO_BACK_BUTTON_Y}, {GO_BACK_BUTTON_WIDTH, GO_BACK_BUTTON_HEIGHT})});
    goBackButtonEngine->getComponent<Engine::AnimationComponent>()->addAnimation(Engine::ButtonComponent::ButtonState::CLICKED, {Engine::Box<double>({GO_BACK_BUTTON_X_CLICKED, GO_BACK_BUTTON_Y}, {GO_BACK_BUTTON_WIDTH, GO_BACK_BUTTON_HEIGHT})});

    auto enableFullscreenText = std::make_unique<SpriteSFML>(FULLSCREEN_TEXT_PATH);
    std::shared_ptr<Engine::Entity> enableFullscreenEngine = std::make_shared<Engine::Drawable>(Engine::Point<double>{FULLSCREEN_TEXT_POSITION_X, FULLSCREEN_TEXT_POSITION_Y}, std::move(enableFullscreenText));

    auto framerateText = std::make_unique<SpriteSFML>(FRAMERATE_TEXT_PATH);
    std::shared_ptr<Engine::Entity> framerateEngine = std::make_shared<Engine::Drawable>(Engine::Point<double>{FRAMERATE_TEXT_POSITION_X, FRAMERATE_TEXT_POSITION_Y}, std::move(framerateText));

    auto vsyncText = std::make_unique<SpriteSFML>(VSYNC_TEXT_PATH);
    std::shared_ptr<Engine::Entity> vsyncEngine = std::make_shared<Engine::Drawable>(Engine::Point<double>{VSYNC_TEXT_POSITION_X, VSYNC_TEXT_POSITION_Y}, std::move(vsyncText));

    auto musicText = std::make_unique<SpriteSFML>(MUSIC_TEXT_PATH);
    std::shared_ptr<Engine::Entity> musicEngine = std::make_shared<Engine::Drawable>(Engine::Point<double>{MUSIC_TEXT_POSITION_X, MUSIC_TEXT_POSITION_Y}, std::move(musicText));

    auto soundEffectsText = std::make_unique<SpriteSFML>(SOUND_EFFECTS_TEXT_PATH);
    std::shared_ptr<Engine::Entity> soundEffectsEngine = std::make_shared<Engine::Drawable>(Engine::Point<double>{SOUND_EFFECTS_TEXT_POSITION_X, SOUND_EFFECTS_TEXT_POSITION_Y}, std::move(soundEffectsText));

    this->spawnEntity(enableFullscreenEngine);
    this->spawnEntity(framerateEngine);
    this->spawnEntity(vsyncEngine);
    this->spawnEntity(musicEngine);
    this->spawnEntity(soundEffectsEngine);
    this->spawnEntity(goBackButtonEngine);

    auto onOffFTextWindowEnableFullscreen = std::make_unique<SpriteSFML>(ON_OFF_PATH);
    onOffFTextWindowEnableFullscreen ->setRect({Engine::Box<double>({0, 0}, {ON_OFF_WIDTH, ON_OFF_HEIGHT})});
    createSelector({static_cast<double>(LEFT_BUTTON_FULLSCREEN_POSITION_X),static_cast<double>(RIGHT_BUTTON_FULLSCREEN_POSITION_Y)}, {changeWindowEnableFullscreen, changeWindowEnableFullscreen}, ON_OFF_PATH, std::move(onOffFTextWindowEnableFullscreen ));
    auto framerateTextNumber = std::make_unique<SpriteSFML>(FRAMERATE_VALUE_PATH);
    framerateTextNumber->setRect({Engine::Box<double>({0, 0}, {FRAMERATE_VALUE_WIDTH, FRAMERATE_VALUE_HEIGHT})});
    createSelector({static_cast<double>(LEFT_BUTTON_FRAMERATE_POSITION_X),static_cast<double>(RIGHT_BUTTON_FRAMERATE_POSITION_Y)}, {changeWindowFrameratePrev, changeWindowFramerateNext}, FRAMERATE_VALUE_PATH, std::move(framerateTextNumber));
    auto onOffFTextWindowVSync = std::make_unique<SpriteSFML>(ON_OFF_PATH);
    onOffFTextWindowVSync->setRect({Engine::Box<double>({0, 0}, {ON_OFF_WIDTH, ON_OFF_HEIGHT})});
    createSelector({static_cast<double>(LEFT_BUTTON_VSYNC_POSITION_X),static_cast<double>(RIGHT_BUTTON_VSYNC_POSITION_Y)}, {changeWindowVsync, changeWindowVsync}, ON_OFF_PATH, std::move(onOffFTextWindowVSync));
    auto onOffFTextMusicEnabled = std::make_unique<SpriteSFML>(ON_OFF_PATH);
    onOffFTextMusicEnabled->setRect({Engine::Box<double>({0, 0}, {ON_OFF_WIDTH, ON_OFF_HEIGHT})});
    createSelector({static_cast<double>(LEFT_BUTTON_MUSIC_POSITION_X),static_cast<double>(RIGHT_BUTTON_MUSIC_POSITION_Y)}, {changeAudioEnableMusic, changeAudioEnableMusic}, ON_OFF_PATH, std::move(onOffFTextMusicEnabled));
    auto onOffFTextSoundEffectEnabled = std::make_unique<SpriteSFML>(ON_OFF_PATH);
    onOffFTextSoundEffectEnabled->setRect({Engine::Box<double>({0, 0}, {ON_OFF_WIDTH, ON_OFF_HEIGHT})});
    createSelector({static_cast<double>(LEFT_BUTTON_SOUND_EFFECTS_POSITION_X),static_cast<double>(RIGHT_BUTTON_SOUND_EFFECTS_POSITION_Y)} , {changeAudioEnableSoundEffects, changeAudioEnableSoundEffects}, ON_OFF_PATH, std::move(onOffFTextSoundEffectEnabled));
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

std::vector<std::shared_ptr<Engine::Entity>> Settings::getSettingsEntities() const
{
    return _settingsEntities;
}
