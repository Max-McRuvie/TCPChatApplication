#ifndef SERVER_UTILS_H
#define SERVER_UTILS_H

#include <stdio.h>
#include <winsock2.h>
#include <ws2tcpip.h>


#define PORT 8080
#define BUFFER_SIZE 1024


// Server functions
int initialize_winsock(WSADATA *wsa_data);
SOCKET create_server_socket(int port);
int server_listen(SOCKET server_socket, struct sockaddr_in *server_addr);
SOCKET accept_client(SOCKET server_socket, struct sockaddr_in *client_addr);
void handle_client(SOCKET client_socket);
void cleanup(SOCKET server_socket);

#endif