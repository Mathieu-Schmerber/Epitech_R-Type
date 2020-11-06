#include "TcpSocket.hpp"

void testServer()
{
    Server server(4242);

    server.run();
}

#include "networking/AUdpSocketIO.hpp"

[[noreturn]] void testUdp()
{
    Engine::AUdpSocketIO udp("127.0.0.1", 4242, 4243);

    while (true) {
        std::vector<int> c;
        c.push_back(0);
        c.push_back(1);
        udp.sendDataToServer(c);
        /*for (auto &b : a) {
            std::cout << b << " ";
        }
        std::cout << std::endl;*/
        Sleep(2000);
    }
}

int main()
{
    testUdp();
    return 0;
}