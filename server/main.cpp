#include "TCP/TcpSocket.hpp"

void testServer()
{
    Server server(4242);

    server.run();
}

int main()
{
    testServer();
    return 0;
}