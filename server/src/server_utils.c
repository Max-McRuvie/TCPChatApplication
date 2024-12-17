#include <stdio.h>
#include <winsock2.h>
#include <ws2tcpip.h>
#include "server_utils.h"

// Server functions
int initialize_winsock(WSADATA *wsa_data){
    return WSAStartup(MAKEWORD(2, 2), wsa_data);
}

SOCKET create_server_socket(int port) {
    SOCKET server_socket = socket(AF_INET, SOCK_STREAM, 0);
    if (server_socket == INVALID_SOCKET) {
        printf("Failed to create socket. Error Code: %d\n", WSAGetLastError());
        WSACleanup();
        return INVALID_SOCKET;
    }

    struct sockaddr_in server_addr;
    server_addr.sin_family = AF_INET;
    server_addr.sin_addr.s_addr = INADDR_ANY;   // Bind to all available interfaces
    server_addr.sin_port = htons(port);         // Use the provided port

    // Bind the socket to the specified port
    if (bind(server_socket, (struct sockaddr*)&server_addr, sizeof(server_addr)) == SOCKET_ERROR) {
        printf("Bind failed. Error Code: %d\n", WSAGetLastError());
        closesocket(server_socket);
        WSACleanup();
        return INVALID_SOCKET;
    }

    printf("Server socket created and bound to port %d.\n", port);
    return server_socket;  // Return the bound server socket
}

int server_listen(SOCKET server_socket, struct sockaddr_in *server_addr){
    // Listen
    if (listen(server_socket, 3) == SOCKET_ERROR) {
        printf("Listen failed. Error Code: %d\n", WSAGetLastError());
        closesocket(server_socket);
        WSACleanup();
        return EXIT_FAILURE;
    }

    printf("Server is listening for incomming connections.\n");
    return EXIT_SUCCESS;
}

SOCKET accept_client(SOCKET server_socket, struct sockaddr_in *client_addr) {
    int addr_len = sizeof(*client_addr);
    SOCKET client_socket = accept(server_socket, (struct sockaddr *)client_addr, &addr_len);
    if (client_socket == INVALID_SOCKET) {
        printf("Accept failed. Error: %d\n", WSAGetLastError());
    }
    return client_socket;
}

void handle_client(SOCKET client_socket) {
    char buffer[BUFFER_SIZE];
    int bytes_received = recv(client_socket, buffer, BUFFER_SIZE, 0);
    if (bytes_received > 0) {
        buffer[bytes_received] = '\0';
        printf("Received: %s\n", buffer);
        send(client_socket, buffer, bytes_received, 0);
    }
    closesocket(client_socket);
}

void cleanup(SOCKET server_socket) {
    closesocket(server_socket);
    WSACleanup();
}

