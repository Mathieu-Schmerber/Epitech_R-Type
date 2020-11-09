//
// Created by mathi on 06/11/2020.
//

#ifndef RTYPE_SOCKETPARSER_HPP
#define RTYPE_SOCKETPARSER_HPP

#include <vector>
#include "ecs/Entity.hpp"
#include "enumerations/Inputs.hpp"

class SocketParser
{
public:
    [[nodiscard]] static std::vector<int> parseUdpInputs(int clientId,
                                                         const std::vector<Engine::Inputs> &pressed,
                                                         const std::vector<Engine::Inputs> &released);

    [[nodiscard]] static std::shared_ptr<Engine::Entity> unparseUdpEntity(const std::vector<int> &in);
    static void updateEntityFromUdp(std::shared_ptr<Engine::Entity> &entity, const std::vector<int> &in);

    [[nodiscard]] static std::shared_ptr<Engine::Entity> unparseTcpLobby(const std::vector<int> &in);
    static void updateLobbyTcpUdp(std::shared_ptr<Engine::Entity> &lobby, const std::vector<int> &in);
};


#endif //RTYPE_SOCKETPARSER_HPP
