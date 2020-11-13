#include "TCP/TcpSocket.hpp"
#include "Client.hpp"
#include "tools/DLLoader.hpp"

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