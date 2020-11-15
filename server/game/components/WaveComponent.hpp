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
            {basic, "Basic.txt"},
            {medium, "Medium.txt"},
            {hard, "Hard.txt"},
            {boss, "Boss.txt"}
    };
    std::map<int, int> _waveDuration = {
            {basic, 3},
            {medium, 3},
            {hard, 3},
            {boss, 3}
    };
    int displayWaveTime = 2;
    int _currentWave = basic;

public:
    explicit WaveComponent() = default;

    enum wave {
        basic = 0,
        medium = 1,
        hard = 2,
        boss = 3
    };

    std::string getTextFromWave(int wnb) {return _waveText.at(wnb);}
    int getDurationFromWave(int wnb) {return _waveDuration.at(wnb);}
    [[nodiscard]] bool timeToSwitch() {return _currentWave < 3 && Engine::Timer::hasElapsed(_lastChgmt, getDurationFromWave(_currentWave));}
    void goNextScene() {
        _currentWave += 1;
        _lastChgmt = std::chrono::high_resolution_clock::now();
    }
    double getElapsedSecondSinceLastStart() {return Engine::Timer::getElapsed(_lastChgmt);}
    [[nodiscard]] int getCurrentWave() const {return _currentWave;}
};

#endif //RTYPE_WAVECOMPONENT_HPP