#include <iostream>
#include <winsock2.h>
using namespace std;

#pragma comment(lib, "ws2_32.lib")

int main()
{
    WSADATA wsa;
    WSAStartup(MAKEWORD(2, 2), &wsa);

    SOCKET clientSocket;
    sockaddr_in server;

    clientSocket = socket(AF_INET, SOCK_DGRAM, 0);

    server.sin_family = AF_INET;
    server.sin_addr.s_addr = inet_addr("127.0.0.1");
    server.sin_port = htons(5001);

    char buffer[1024];

    cout << "UDP Client started!" << endl;

    while (true)
    {
        string message;

        cout << "Client: ";
        getline(cin, message);

        sendto(clientSocket, message.c_str(),
               message.length(), 0,
               (sockaddr*)&server, sizeof(server));

        if (message == "exit")
            break;

        ZeroMemory(buffer, sizeof(buffer));

        sockaddr_in from;
        int size = sizeof(from);

        int bytes = recvfrom(clientSocket, buffer,
                    sizeof(buffer)-1, 0,
                    (sockaddr*)&from, &size);

        if (bytes <= 0)
            break;

        buffer[bytes] = '\0';

        cout << "Server: " << buffer << endl;

        if (string(buffer) == "exit")
            break;
    }

    closesocket(clientSocket);
    WSACleanup();

    return 0;
}