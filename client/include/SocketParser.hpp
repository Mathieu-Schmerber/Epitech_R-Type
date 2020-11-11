//
// Created by mathi on 06/11/2020.
//

#ifndef RTYPE_SOCKETPARSER_HPP
#define RTYPE_SOCKETPARSER_HPP

#include <vector>
#include "ecs/Entity.hpp"
#include "enumerations/Inputs.hpp"
#include "tools/AssetPool.hpp"
#include "tools/Timer.hpp"
#include "tools/Geometry.hpp"

class SocketParser
{
private:
    std::unique_ptr<Engine::AssetPool> _pool;
    std::unique_ptr<Engine::Timer> _timer;
    std::unique_ptr<Engine::Timer> _serverTimer;
    double _serverDelta;
    double _deltatime;
    bool _serverUpdate;

    [[nodiscard]] static Engine::Point<int> lerp(Engine::Point<int> a, Engine::Point<int> b, double time);

public:
    SocketParser();

    [[nodiscard]] static std::vector<int> parseUdpInputs(int clientId,
                                                         const std::vector<Engine::Inputs> &pressed,
                                                         const std::vector<Engine::Inputs> &released);

    [[nodiscard]] std::shared_ptr<Engine::Entity> unparseUdpEntity(const std::vector<int> &in);
    void updateEntityFromUdp(std::shared_ptr<Engine::Entity> &entity, const std::vector<int> &in);

    [[nodiscard]] static std::shared_ptr<Engine::Entity> unparseTcpLobby(const std::vector<int> &in);
    static void updateLobbyFromTcp(std::shared_ptr<Engine::Entity> &lobby, const std::vector<int> &in);

    void refreshTimer(bool dataChanged);
};


#endif //RTYPE_SOCKETPARSER_HPP
