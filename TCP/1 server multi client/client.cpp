#include <iostream>
#include <winsock2.h>
#include <string>
using namespace std;

#pragma comment(lib, "ws2_32.lib")

int main()
{
    WSADATA wsa;
    WSAStartup(MAKEWORD(2, 2), &wsa);

    SOCKET clientSocket = socket(AF_INET, SOCK_STREAM, 0);

    sockaddr_in server;

    server.sin_family = AF_INET;
    server.sin_port = htons(5000);
    server.sin_addr.s_addr = inet_addr("127.0.0.1");

    if (connect(clientSocket, (sockaddr*)&server,
                sizeof(server)) == SOCKET_ERROR)
    {
        cout << "Connection failed!" << endl;
        closesocket(clientSocket);
        WSACleanup();
        return 1;
    }

    cout << "Connected to server!" << endl;

    string message;
    char buffer[1024];

    while (true)
    {
        cout << "Enter message (exit to quit): ";
        getline(cin, message);

        if (message == "exit")
            break;

        send(clientSocket, message.c_str(),
             message.length(), 0);

        memset(buffer, 0, sizeof(buffer));

        int bytes = recv(clientSocket, buffer,
                         sizeof(buffer)-1, 0);

        if (bytes <= 0)
        {
            cout << "Server disconnected!" << endl;
            break;
        }

        buffer[bytes] = '\0';

        cout << "Server reply: " << buffer << endl;
    }

    closesocket(clientSocket);
    WSACleanup();

    return 0;
}