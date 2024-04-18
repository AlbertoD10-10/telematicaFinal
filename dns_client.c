#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <winsock2.h>
#include <ws2tcpip.h>

#define BUFFER_SIZE 256

void dns_query(const char *server_ip, int server_port, const char *query) { // Enviar consulta DNS y recibir la respuesta
    SOCKET client_socket;
    struct sockaddr_in server_addr;
    char buffer[BUFFER_SIZE];
    
    // Inicializacion del  Winsock
    WSADATA wsaData;
    if (WSAStartup(MAKEWORD(2, 2), &wsaData) != 0) {
        fprintf(stderr, "Error al inicializar Winsock\n");
        exit(EXIT_FAILURE);
    }

    // Crear un socket UDP
    client_socket = socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP);
    if (client_socket == INVALID_SOCKET) {
        fprintf(stderr, "Error al crear el socket: %d\n", WSAGetLastError());
        WSACleanup();
        exit(EXIT_FAILURE);
    }

    // dirección del servidor
    memset(&server_addr, 0, sizeof(server_addr));
    server_addr.sin_family = AF_INET;
    server_addr.sin_port = htons(server_port);
    server_addr.sin_addr.s_addr = inet_addr(server_ip);

    // Verificacion y envio de la consulta DNS al servidor
    if (sendto(client_socket, query, strlen(query), 0, (struct sockaddr *)&server_addr, sizeof(server_addr)) == SOCKET_ERROR) {
        fprintf(stderr, "Error al enviar la consulta DNS: %d\n", WSAGetLastError());
        closesocket(client_socket);
        WSACleanup();
        exit(EXIT_FAILURE);
    }

    // Recibir la respuesta DNS por parte del servidor
    int recv_len = recvfrom(client_socket, buffer, BUFFER_SIZE, 0, NULL, NULL);
    if (recv_len == SOCKET_ERROR) {
        fprintf(stderr, "Error al recibir la respuesta DNS: %d\n", WSAGetLastError());
        closesocket(client_socket);
        WSACleanup();
        exit(EXIT_FAILURE);
    }


    buffer[recv_len] = '\0'; 
    printf("Respuesta recibida: %s\n", buffer);

    // Cierr del socket
    closesocket(client_socket);

    // Limpiar Winsock
    WSACleanup();
}

// Función principal del cliente DNS
int main(int argc, char *argv[]) {
    if (argc != 4) {
        fprintf(stderr, "Uso: %s <server_ip> <server_port> <consulta>\n", argv[0]);
        return EXIT_FAILURE;
    }

    const char *server_ip = argv[1];
    int server_port = atoi(argv[2]);
    const char *query = argv[3];

    // Enviar la consulta DNS y recibir la respuesta
    dns_query(server_ip, server_port, query);

    return EXIT_SUCCESS;
}
