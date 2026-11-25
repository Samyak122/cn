#include <iostream>
#include <winsock2.h>
using namespace std;

int main()
{
    WSADATA wsa;
    SOCKET server, client;
    struct sockaddr_in serverAddr, clientAddr;
    int size = sizeof(clientAddr);
    char msg[1024] = {0};

    // Initialize Winsock
    WSAStartup(MAKEWORD(2,2), &wsa);

    // Create socket
    server = socket(AF_INET, SOCK_STREAM, 0);

    // Set server address
    serverAddr.sin_family = AF_INET;
    serverAddr.sin_port = htons(5000);
    serverAddr.sin_addr.s_addr = INADDR_ANY;

    // Bind socket
    bind(server, (struct sockaddr*)&serverAddr, sizeof(serverAddr));

    // Listen for client
    listen(server, 1);
    cout << "Server waiting for client..." << endl;

    // Accept client
    client = accept(server, (struct sockaddr*)&clientAddr, &size);
    cout << "Client connected!" << endl;

    // Receive message
    recv(client, msg, sizeof(msg), 0);
    cout << "Client: " << msg << endl;

    // Send reply
    string reply = "Hello from TCP Server";
    send(client, reply.c_str(), reply.length(), 0);

    // Close sockets
    closesocket(client);
    closesocket(server);
    WSACleanup();

    return 0;
}

//g++ server.cpp -o server.exe -lws2_32
//.\server.exe