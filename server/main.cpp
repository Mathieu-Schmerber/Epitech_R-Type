#include "TCP/TcpSocket.hpp"

void testServer()
{
    Server server(4242);

    server.run();
}

#include "networking/AUdpSocketIO.hpp"

[[noreturn]] void testClientTcp()
{
    Engine::ATcpSocket tcp("127.0.0.1", 4242);

    while (true) {
        tcp.getDataFromServer();
        Sleep(2000);
    }
}

int main()
{
    testClientTcp();
    return 0;
}