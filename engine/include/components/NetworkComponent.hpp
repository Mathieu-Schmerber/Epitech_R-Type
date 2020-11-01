//
// Created by mathi on 31/10/2020.
//

#ifndef RTYPE_NETWORKCOMPONENT_HPP
#define RTYPE_NETWORKCOMPONENT_HPP

#include "ecs/Component.hpp"

namespace Engine {

    class NetworkComponent : public Engine::Component {
    private:
        const int _networkIdentity;

    public:
        explicit NetworkComponent(int id = 0) : _networkIdentity(id), Component() {}
        ~NetworkComponent() = default;

        int getNetworkId() const {return this->_networkIdentity;}
    };

}

#endif //RTYPE_NETWORKCOMPONENT_HPP