#ifndef CLIENT_UTILS_H
#define CLIENT_UTILS_H

#include <stdio.h>
#include <winsock2.h>
#include <ws2tcpip.h>

#define DEFAULT_PORT 8080
#define BUFFER_SIZE 1024

int initialize_winsock(WSADATA *wsa_data);
SOCKET create_client_socket();
int connect_to_server(SOCKET client_socket, const char *ip_address, int port);
void cleanup(SOCKET socket);

#endif