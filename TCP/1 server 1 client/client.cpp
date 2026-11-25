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

    clientSocket = socket(AF_INET, SOCK_STREAM, 0);

    server.sin_family = AF_INET;
    server.sin_addr.s_addr = inet_addr("127.0.0.1");
    server.sin_port = htons(5000);

    connect(clientSocket, (sockaddr*)&server, sizeof(server));

    cout << "Connected to TCP Server!" << endl;

    char buffer[1024];

    while (true)
    {
        string message;

        cout << "Client: ";
        getline(cin, message);

        send(clientSocket, message.c_str(), message.length(), 0);

        if (message == "exit")
            break;

        ZeroMemory(buffer, sizeof(buffer));

        int bytes = recv(clientSocket, buffer, sizeof(buffer)-1, 0);

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


// g++ client.cpp -o client.exe -lws2_32
// .\client.exe