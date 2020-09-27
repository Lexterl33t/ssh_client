#include <stdio.h>
#include <stdlib.h>
#include <winsock2.h>
#include <string.h>
#include "../includes/ssh_client.h"

#define BUFFERSIZE 4096

/*
    /////////////////////
    |  SOCKET SECTION  |
    ////////////////////

*/

void socket_init(ssh_client_t *ssh)
{
    WSADATA wsaData = {0};
    int iResult = 0;
    SOCKET sock;

    iResult = WSAStartup(MAKEWORD(2, 2), &wsaData);
    if (iResult != 0) {
        wprintf(L"WSAStartup failed: %d\n", iResult);
        exit(EXIT_FAILURE);
    }

    sock = socket(AF_INET, SOCK_STREAM, 0);
    ssh->fd = sock;

}

void socket_connect(ssh_client_t *ssh)
{
    struct sockaddr_in sin;

    sin.sin_family = AF_INET;
    sin.sin_port = htons(22); // ssh port default
    sin.sin_addr.s_addr = inet_addr(ssh->host); //inet_addr to convert host to network bytes 
    if(connect(ssh->fd, (struct sockaddr *)&sin, sizeof(sin)) < 0) {
        printf("Error connection !!!\n");
        exit(EXIT_FAILURE);
    }

}


/*
    /////////////////////
    |    SSH SECTION   |
    ////////////////////

*/

void ssh_get_info(ssh_client_t *ssh, ssh_server_info_t *ssh_servr)
{
    ssh_server_info_t *ssh_server = malloc(sizeof(ssh_server_info_t));
    char *buffer = malloc(4);
    char protocol[256];
    char service[256];
    char version[256];

    recv(ssh->fd, buffer, BUFFERSIZE, 0);
    

    while(*(buffer) && *(buffer) != '-') {
        strcat(protocol, buffer);
        *(buffer)++;
    }

    printf("%s\n", protocol);
        

    
}

ssh_client_t *ssh_login(char *host, char *username, char *password)
{
    ssh_client_t *ssh = malloc(sizeof(ssh_client_t));
    ssh_server_info_t *ssh_server = malloc(sizeof(ssh_server_info_t));

    char buffer[BUFFERSIZE];

    if(strcmp("localhost", host) == 0)
        ssh->host = "127.0.0.1";
    else
        ssh->host = host;

    ssh->user = username;
    ssh->pass = password;

    socket_init(ssh);
    socket_connect(ssh);

    return (ssh);
}
