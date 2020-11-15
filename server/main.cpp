#include "TCP/TcpSocket.hpp"
#include "Client.hpp"
#include "tools/DLLoader.hpp"

void startServer()
{
    Server server(4242);

    server.run();
}

int main()
{
    try {
        startServer();
    } catch (std::exception &e) {
        std::cerr << "Fatal error " << e.what() << std::endl;
    }
    return 0;
}