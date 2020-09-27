#pragma once


typedef struct ssh_client_t ssh_client_t;
typedef struct ssh_server_info_t ssh_server_info_t;

struct ssh_client_t {
    char *host;
    char *user;
    char *pass;
    int fd;
};

struct ssh_server_info_t {
    char *protocol;
    char *version;
    char *service;
};


void socket_init(ssh_client_t *ssh);
void socket_connect(ssh_client_t *ssh);
ssh_client_t *ssh_login(char *host, char *username, char *password);
void ssh_get_info(ssh_client_t *ssh, ssh_server_info_t *ssh_servr);
