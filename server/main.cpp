#include "TCP/TcpSocket.hpp"
#include "game/IEnemy.hpp"
#include "game/DLLoader.hpp"

void testServer()
{
    Server server(4242);

    server.run();
}

void testSharedLibs(std::string arg)
{
    auto dl = new DLLoader<IEnemy *>(arg);
    dl->open();
    auto i = dl->getInstance();
    i->test2();
}

#include "networking/AUdpSocketIO.hpp"

int main(int ac, char **av)
{
    testServer();
    return 0;
}