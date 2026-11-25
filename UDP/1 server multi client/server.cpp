#include <iostream>
#include <winsock2.h>
using namespace std;

#pragma comment(lib, "ws2_32.lib")

int main()
{
    WSADATA wsa;
    WSAStartup(MAKEWORD(2, 2), &wsa);

    SOCKET serverSocket;
    sockaddr_in server, client;

    serverSocket = socket(AF_INET, SOCK_DGRAM, 0);

    server.sin_family = AF_INET;
    server.sin_addr.s_addr = INADDR_ANY;
    server.sin_port = htons(5001);

    bind(serverSocket, (sockaddr*)&server, sizeof(server));

    cout << "UDP Server waiting for messages..." << endl;

    int size = sizeof(client);
    char buffer[1024];

    while (true)
    {
        ZeroMemory(buffer, sizeof(buffer));

        int bytes = recvfrom(serverSocket, buffer,
                    sizeof(buffer)-1, 0,
                    (sockaddr*)&client, &size);

        if (bytes == SOCKET_ERROR)
            break;

        buffer[bytes] = '\0';

        cout << "Client: " << buffer << endl;

        if (string(buffer) == "exit")
            break;

        string reply;
        cout << "Server: ";
        getline(cin, reply);

        sendto(serverSocket, reply.c_str(),
               reply.length(), 0,
               (sockaddr*)&client, size);

        if (reply == "exit")
            break;
    }

    closesocket(serverSocket);
    WSACleanup();

    return 0;
}

// g++ udp_server.cpp -o udp_server.exe -lws2_32
// .\udp_server.exe