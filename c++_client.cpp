#include <iostream>
#include <list>
#include "targetver.h"
#include <winsock2.h>
#include <ws2tcpip.h>
#include "stdafx.h"
#include <winsock.h>

using namespace std;



int main(int argc, char* argv[]) {

    WSADATA wsaData;
    int wsaerr;
    WORD wVersionRequested = MAKEWORD(2, 2);
    wsaerr = WSAStartup(wVersionRequested, &wsaData);

    if (wsaerr != 0) {
        cout << "The Winsock dll not found!" << endl;
    }
    else {
        cout << "The Winsock dll found!" << endl;
        cout << "The status: " << wsaData.szSystemStatus << endl;
    }

    // create socket

    SOCKET clientSocket = INVALID_SOCKET;
    clientSocket = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
    if (clientSocket == INVALID_SOCKET) {
        cout << "Error socket(): " << WSAGetLastError() << endl;
        WSACleanup();
        return 0;
    }
    else {
        cout << "socket() is OK!" << endl;
    }


    // connect (bind is going automaticly)

    sockaddr_in clientService;

    clientService.sin_family = AF_INET;
    InetPton(AF_INET, _T("127.0.0.1"), &clientService.sin_addr.s_addr);
    clientService.sin_port = htons(55555);

    if (connect(clientSocket, (SOCKADDR*)&clientService, sizeof(clientService)) == SOCKET_ERROR) {
        cout << "Client: connect() - Failed connect " << WSAGetLastError() << endl;
        closesocket(clientSocket);
        WSACleanup();
        return 0;
    }
    else {
        cout << "Client: connect() is OK!" << endl;
        cout << "Client: Can sendinig and receiving data..." << endl;

    }


    // TCP transmission (sending)

    char buffer[200];
    cout << "Enter your messege: " << endl;
    cin.getline(buffer, 200);
    int byteCount = send(clientSocket, buffer, sizeof(buffer), 0);
    if (byteCount == SOCKET_ERROR) {
        cout << "Server send error" << WSAGetLastError() << endl;
        return -1;
    }
    else {
        cout << "Client: " << byteCount << " bytes have been sent" << endl;
        // printf("Server: sent %ld bytes\n ", byteCount);
    }


    system("pause>0");
    return 0;
}
