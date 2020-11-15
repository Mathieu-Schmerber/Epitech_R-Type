//
// Created by mathi on 15/11/2020.
//

#ifndef RTYPE_BORDERLIMITSYSTEM_HPP
#define RTYPE_BORDERLIMITSYSTEM_HPP

#include "ecs/System.hpp"
#include "Game.hpp"

class BorderLimitSystem : public Engine::System {
private:
    std::shared_ptr<Game> _game;

public:
    explicit BorderLimitSystem(std::shared_ptr<Game> &game);

    void update() override;
};


#endif //RTYPE_BORDERLIMITSYSTEM_HPP
