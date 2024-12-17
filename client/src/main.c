#include <stdio.h>
#include <winsock2.h>
#include <ws2tcpip.h>
#include "client_utils.h"

#define DEFAULT_PORT 8080
#define BUFFER_SIZE 1024

int main(){
    WSADATA wsa_data;
    SOCKET client_socket;
    struct sockaddr_in server_addr;
    const char *ip_address = "127.0.0.1";
    char buffer[BUFFER_SIZE];

    // Initialize Winsock
    if (initialize_winsock(&wsa_data) != 0) {
        printf("Winsock initialization failed.\n");
        return EXIT_FAILURE;
    }

    // Create socket
    client_socket = create_client_socket();
    if (client_socket == INVALID_SOCKET) {
        printf("Failed to create socket. Error Code: %d\n", WSAGetLastError());
        WSACleanup();
        return EXIT_FAILURE;
    }

    // Connect to server
    if(connect_to_server(client_socket, ip_address, DEFAULT_PORT) != 0){
        cleanup(client_socket);
        return EXIT_FAILURE;
    }
    
    // Communication loop
    while(1){
        // Send data to server
        const char *message = "Hello from client";
        send(client_socket, message, strlen(message), 0);

        // Receive response from server
        int bytesReceived = recv(client_socket, buffer, BUFFER_SIZE, 0);
        if (bytesReceived > 0) {
            buffer[bytesReceived] = '\0'; // Null-terminate the received data
            printf("Received from server: %s\n", buffer);
        }

        Sleep(500);
    }

    // Cleanup
    closesocket(client_socket);
    WSACleanup();
    return EXIT_SUCCESS;
}