#include <iostream>
#include <winsock2.h>
#include <windows.h>
#include <thread>
#include <string>
using namespace std;

#pragma comment(lib, "ws2_32.lib")

void handleClient(SOCKET clientSocket, int clientNo)
{
    char buffer[1024];

    cout << "\nClient " << clientNo << " connected!" << endl;

    while (true)
    {
        memset(buffer, 0, sizeof(buffer));

        int bytes = recv(clientSocket, buffer, sizeof(buffer)-1, 0);

        if (bytes <= 0)
        {
            cout << "Client " << clientNo
                 << " disconnected." << endl;
            break;
        }

        buffer[bytes] = '\0';

        cout << "Client " << clientNo << ": "
             << buffer << endl;

        if (string(buffer) == "exit")
            break;

        string reply = "Message received by server!";

        send(clientSocket, reply.c_str(),
             reply.length(), 0);
    }

    closesocket(clientSocket);
}

int main()
{
    WSADATA wsa;
    WSAStartup(MAKEWORD(2, 2), &wsa);

    SOCKET serverSocket = socket(AF_INET, SOCK_STREAM, 0);

    sockaddr_in server;

    server.sin_family = AF_INET;
    server.sin_port = htons(5000);
    server.sin_addr.s_addr = INADDR_ANY;

    bind(serverSocket, (sockaddr*)&server, sizeof(server));

    listen(serverSocket, 5);

    cout << "TCP Server started on port 5000..." << endl;
    cout << "Waiting for clients..." << endl;

    int clientNo = 0;

    while (true)
    {
        SOCKET clientSocket = accept(serverSocket, NULL, NULL);

        if (clientSocket == INVALID_SOCKET)
            continue;

        clientNo++;

        thread(handleClient, clientSocket, clientNo).detach();
    }

    closesocket(serverSocket);
    WSACleanup();

    return 0;
}