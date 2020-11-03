#include "TcpSocket.hpp"

int main()
{
    Server server(4242);

    server.run();
    return 0;
}