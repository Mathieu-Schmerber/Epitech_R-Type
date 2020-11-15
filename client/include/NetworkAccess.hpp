/*!
 * @file NetworkAccess.hpp
 * @brief NetworkAccess module declaration
 * @authors Mathieu.S
 * @version 1.0
 * @date 14/11/2020
 *
*/

#ifndef RTYPE_NETWORKACCESS_HPP
#define RTYPE_NETWORKACCESS_HPP

#include "networking/AServer.hpp"

class NetworkAccess : public Engine::AServer
{
private:
    short _clientId;

public:
    /*!
    * \brief NetworkAcces constructor
    * \param ip ip to be set
    * \param serverPort serverPort to be set
    * \param clientPort clientPort to be set
    *
   */
    NetworkAccess(const std::string &ip, short serverPort, short clientPort)
    : _clientId(-1), Engine::AServer(ip, serverPort, clientPort) {}

    [[nodiscard]] short getClientId() const {return _clientId;}
    void setClientId(short clientId) {_clientId = clientId;}
};


#endif //RTYPE_NETWORKACCESS_HPP
