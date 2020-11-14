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
    int _currentWave = basic;

public:
    explicit WaveComponent() = default;

    enum wave {
        basic = 0,
        medium = 1,
        hard = 2,
        boss = 3
    };

    std::string getTextFromWave(wave wnb) {return _waveText.at(wnb);}

private:
    std::map<wave, std::string> _waveText = {{basic, "Basic.txt"}};

};

#endif //RTYPE_WAVECOMPONENT_HPP