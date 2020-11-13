//
// Created by mathi on 29/10/2020.
//

#ifndef RTYPE_AUDPSOCKETIO_HPP
#define RTYPE_AUDPSOCKETIO_HPP

#include "networking/UDP/UdpSocketInput.hpp"
#include "networking/UDP/UdpSocketOutput.hpp"

namespace Engine {
    class AUdpSocketIO : public UdpSocketInput, public UdpSocketOutput {
    public:
        AUdpSocketIO(const std::string &ipServer, int portServer, int portClient);
    };
}

#endif //RTYPE_AUDPSOCKETIO_HPP
