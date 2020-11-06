#include "TCP/TcpSocket.hpp"

void testServer()
{
    Server server(4242);

    server.run();
}

#include "networking/AUdpSocketIO.hpp"

int main()
{
    return 0;
}