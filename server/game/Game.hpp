//
// Created by mathi on 06/11/2020.
//

#ifndef RTYPE_GAME_HPP
#define RTYPE_GAME_HPP

#include "ecs/System.hpp"
#include "tools/Timer.hpp"
#include "networking/UDP/UdpSocketInput.hpp"
#include "Client.hpp"

class Game
{
private:
    bool _running;
    int _idIncrement;
    std::unique_ptr<Engine::Timer> _timer;
    std::vector<std::unique_ptr<Engine::System>> _systems;
    std::vector<std::shared_ptr<Engine::Entity>> _entities;
    std::vector<std::shared_ptr<Client>> _players;
    std::reference_wrapper<std::unique_ptr<UdpSocketInput>> _reception;


    void initGameEntities();
    void initGameSystems();

public:
    Game(std::vector<std::shared_ptr<Client>> &players, std::unique_ptr<UdpSocketInput> &reception);
    ~Game();

    void spawn(std::shared_ptr<Engine::Entity> &entity, bool addToNetwork);
    void update();
    [[nodiscard]] bool isGameRunning() const;
};


#endif //RTYPE_GAME_HPP