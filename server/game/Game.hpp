//
// Created by mathi on 06/11/2020.
//

#ifndef RTYPE_GAME_HPP
#define RTYPE_GAME_HPP

#include <entities/Enemy.hpp>
#include "ecs/System.hpp"
#include "tools/Timer.hpp"
#include "networking/UDP/UdpSocketInput.hpp"
#include "Client.hpp"
#include "DLLoader.hpp"

class Game : public std::enable_shared_from_this<Game>
{
private:
    bool _running;
    int _idIncrement;
    std::unique_ptr<Engine::Timer> _timer;
    std::vector<std::unique_ptr<Engine::System>> _systems;
    std::vector<std::shared_ptr<Engine::Entity>> _entities;
    std::vector<Client> _players;
    std::reference_wrapper<std::unique_ptr<UdpSocketInput>> _reception;

    DLLoader<Enemy> dynLoader = std::string("../lib/libfloatingRobot.so");

    void initGameEntities();
    void initGameSystems();

public:
    Game(std::vector<Client> &players, std::unique_ptr<UdpSocketInput> &reception);
    ~Game();

    void spawn(std::shared_ptr<Engine::Entity> &entity, bool addToNetwork);
    void despawn(std::shared_ptr<Engine::Entity> &entity);
    void update();
    [[nodiscard]] bool isGameRunning() const;
};


#endif //RTYPE_GAME_HPP