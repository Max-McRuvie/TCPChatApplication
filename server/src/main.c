#include <stdio.h>
#include <winsock2.h>
#include <ws2tcpip.h>
#include "server_utils.h"

#define PORT 8080
#define BUFFER_SIZE 1024

int main() {
    WSADATA wsa_data;
    SOCKET server_socket, client_socket;
    struct sockaddr_in client_addr;

    // Initialize Winsock
    if (initialize_winsock(&wsa_data) != 0) {
        printf("Winsock initialization failed.\n");
        return EXIT_FAILURE;
    }

    // Create and bind server socket
    server_socket = create_server_socket(PORT);
    if (server_socket == INVALID_SOCKET) {
        printf("Failed to create and bind server socket.\n");
        WSACleanup();
        return EXIT_FAILURE;
    }

    // Listen for incoming connections
    if (server_listen(server_socket, &client_addr) == SOCKET_ERROR) {
        printf("Listen failed. Error Code: %d\n", WSAGetLastError());
        cleanup(server_socket);
        return EXIT_FAILURE;
    }

    printf("Server is listening on port %d...\n", PORT);

    // Accept and handle a client connection
    client_socket = accept_client(server_socket, (struct sockaddr*)&client_addr);
    if (client_socket == INVALID_SOCKET) {
        printf("Accept failed. Error Code: %d\n", WSAGetLastError());
    } else {
        handle_client(client_socket);
    }

    // Cleanup server resources
    cleanup(server_socket);
    return EXIT_SUCCESS;
}