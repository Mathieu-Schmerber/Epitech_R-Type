//
// Created by mathi on 10/11/2020.
//

#ifndef RTYPE_WAVECOMPONENT_HPP
#define RTYPE_WAVECOMPONENT_HPP

#include "tools/Timer.hpp"
#include "ecs/Component.hpp"
#include "components/ProjectileComponent.hpp"
#include "CollisionMasks.hpp"

class WaveComponent : public Engine::Component
{
private:
    std::chrono::high_resolution_clock::time_point _lastChgmt = std::chrono::high_resolution_clock::now();
    std::map<int, std::string> _waveText = {
            {basic, "../../client/assets/textsEdt/Basic.txt"},
            {medium, "../../client/assets/textsEdt/Medium.txt"},
            {hard, "../../client/assets/textsEdt/Hard.txt"},
            {boss, "../../client/assets/textsEdt/Boss.txt"},
            {victory, "../../client/assets/textsEdt/Victory.txt"}
    };
    std::map<int, int> _waveDuration = {
            {basic, 10},
            {medium, 10},
            {hard, 10},
            {boss, 10},
            {victory, 4}
    };
    int displayWaveTime = 2;
    int _currentWave = basic;

public:
    explicit WaveComponent() = default;

    enum wave {
        basic = 0,
        medium = 1,
        hard = 2,
        boss = 3,
        victory = 4,
    };

    std::string getTextFromWave(int wnb) {return _waveText.at(wnb);}
    int getDurationFromWave(int wnb) {return _waveDuration.at(wnb);}
    [[nodiscard]] bool timeToSwitch() {return _currentWave < victory && Engine::Timer::hasElapsed(_lastChgmt, getDurationFromWave(_currentWave));}
    void goNextScene() {
        _currentWave += 1;
        _lastChgmt = std::chrono::high_resolution_clock::now();
    }
    double getElapsedSecondSinceLastStart() {return Engine::Timer::getElapsedSeconds(_lastChgmt);}
    [[nodiscard]] int getCurrentWave() const {return _currentWave;}
};

#endif //RTYPE_WAVECOMPONENT_HPP