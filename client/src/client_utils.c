#include <stdio.h>
#include <winsock2.h>
#include <ws2tcpip.h>
#include "client_utils.h"

int initialize_winsock(WSADATA *wsa_data){
    if(WSAStartup(MAKEWORD(2, 2), wsa_data) != 0){
        printf("WSAStartup failed. Error code: %d\n", WSAGetLastError());
        return EXIT_FAILURE;
    }
    return EXIT_SUCCESS;
}

SOCKET create_client_socket(){
    SOCKET client_socket = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
    if (client_socket == INVALID_SOCKET) {
        printf("Failed to create socket. Error Code: %d\n", WSAGetLastError());
        WSACleanup();
        return INVALID_SOCKET;
    }
    return client_socket;
}

int connect_to_server(SOCKET client_socket, const char *ip_address, int port){
    // Setup server address struct
    struct sockaddr_in server_addr;
    memset(&server_addr, 0, sizeof(server_addr)); // Zero out the struct
    server_addr.sin_family = AF_INET;
    server_addr.sin_port = htons(port);

    // Convert IP address string to binary form
    if (inet_pton(AF_INET, ip_address, &server_addr.sin_addr) <= 0) {
        printf("Invalid IP address format.\n");
        return EXIT_FAILURE; // Defined in <stdlib.h>
    }

    // Connect to server
    if (connect(client_socket, (struct sockaddr*)&server_addr, sizeof(server_addr)) == SOCKET_ERROR) {
        printf("Connection failed. Error Code: %d\n", WSAGetLastError());
        closesocket(client_socket);
        WSACleanup();
        return EXIT_FAILURE;
    }

    printf("Connected to server at %s:%d\n", ip_address, port);
    return EXIT_SUCCESS;
}

void cleanup(SOCKET socket){
    closesocket(socket);
    WSACleanup();
}