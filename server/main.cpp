#include "TCP/TcpSocket.hpp"
#include "Client.hpp"
#include "game/DLLoader.hpp"

void testServer()
{
    Server server(4243);

    server.run();
}

int main(int ac, char **av)
{
    testServer();
    return 0;
}