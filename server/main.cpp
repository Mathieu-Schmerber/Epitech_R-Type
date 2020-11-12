#include "TCP/TcpSocket.hpp"
#include "Client.hpp"
#include "game/IEnemy.hpp"
#include "game/DLLoader.hpp"

void testServer()
{
    Server server(4242);

    server.run();
}

int main(int ac, char **av)
{
    testServer();
    return 0;
}