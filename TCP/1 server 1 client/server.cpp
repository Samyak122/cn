
#include <iostream>
#include <winsock2.h>
#include <string>
using namespace std;

int main()
{
    WSADATA wsa;
    SOCKET server, client;
    sockaddr_in serverAddr, clientAddr;
    int size = sizeof(clientAddr);

    char msg[1024];

    // Initialize Winsock
    WSAStartup(MAKEWORD(2,2), &wsa);

    // Create socket
    server = socket(AF_INET, SOCK_STREAM, 0);

    // Set server address
    serverAddr.sin_family = AF_INET;
    serverAddr.sin_port = htons(5000);
    serverAddr.sin_addr.s_addr = INADDR_ANY;

    // Bind socket
    bind(server, (sockaddr*)&serverAddr, sizeof(serverAddr));

    // Listen for client
    listen(server, 1);

    cout << "Server waiting for client..." << endl;

    // Accept client
    client = accept(server, (sockaddr*)&clientAddr, &size);

    cout << "Client connected!" << endl;

    while(true)
    {
        ZeroMemory(msg, sizeof(msg));

        // Receive message
        int bytes = recv(client, msg, sizeof(msg)-1, 0);

        if(bytes <= 0)
            break;

        msg[bytes] = '\0';

        cout << "Client: " << msg << endl;

        // Check exit
        if(string(msg) == "exit")
        {
            send(client, "exit", 4, 0);
            break;
        }

        // Send reply
        string reply = "Hello from TCP Server";

        send(client, reply.c_str(), reply.length(), 0);
    }

    // Close sockets
    closesocket(client);
    closesocket(server);
    WSACleanup();

    return 0;
}


//g++ server.cpp -o server.exe -lws2_32
//.\server.exe