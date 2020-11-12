#include "TCP/TcpSocket.hpp"
#include "entities/Enemy.hpp" // FIXME
#include "game/DLLoader.hpp"  // FIXME
#include "Client.hpp"

void testServer()
{
    Server server(4242);

    server.run();
}

#include "networking/AUdpSocketIO.hpp"

int main(int ac, char **av)
{
    testServer();
    return 0;
}