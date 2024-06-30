// ConsoleApplication1.cpp : This file contains the 'main' function. Program execution begins and ends there.
//
#include <cassert>
#include <cstdio>
#include <WinSock2.h>
#include <ip2string.h>



int main()
{
    WSADATA ws;
    auto error = WSAStartup(MAKEWORD(2, 2), &ws);
    assert(error == 0);

    auto hSocket = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
    assert(hSocket != INVALID_SOCKET);

    sockaddr_in addr{};
    addr.sin_family = AF_INET;
    addr.sin_port = htons(55555);

    error = bind(hSocket, reinterpret_cast<sockaddr*>(&addr), sizeof(addr));
    assert(error == 0);

    error = listen(hSocket, 1);
    assert(error == 0);

    printf("Waiting for connection");
    int len = sizeof(addr);
    auto s = accept(hSocket, (sockaddr*)&addr, &len);
    assert(s != INVALID_SOCKET);

    char address[16];
    RtlIpv4AddressToStringA(&addr.sin_addr, address);
    printf("Connected to %s\n", address);


}

// Run program: Ctrl + F5 or Debug > Start Without Debugging menu
// Debug program: F5 or Debug > Start Debugging menu

// Tips for Getting Started: 
//   1. Use the Solution Explorer window to add/manage files
//   2. Use the Team Explorer window to connect to source control
//   3. Use the Output window to see build output and other messages
//   4. Use the Error List window to view errors
//   5. Go to Project > Add New Item to create new code files, or Project > Add Existing Item to add existing code files to the project
//   6. In the future, to open this project again, go to File > Open > Project and select the .sln file
