/*
** EPITECH PROJECT, 2022
** launch_server.c
** File description:
** launch_server
*/

#include "server.h"

int set_server_socket(int port, client_t *clt)
{
    int sock = socket(AF_INET, SOCK_STREAM, 0);

    if (sock == -1) {
        perror("socket");
        return -1;
    }
    clt->sv_sa_in.sin_family = AF_INET;
    clt->sv_sa_in.sin_addr.s_addr = htonl(INADDR_ANY);
    clt->sv_sa_in.sin_port = htons(port);
    if (bind(sock, (SOCKADDR *)&clt->sv_sa_in, sizeof(clt->sv_sa_in)) == -1) {
        perror("bind");
        return -1;
    }
    if (listen(sock, 25) == -1) {
        perror("listen");
        return -1;
    }
    printf("Listening to port %d...\n", port);
    return sock;
}

client_t **init_clients(void)
{
    client_t **clients = malloc(sizeof(client_t*) * FD_SETSIZE);

    for (int i = 0; i < FD_SETSIZE; i++) {
        clients[i] = malloc(sizeof(client_t));
        clients[i]->tmp = NULL;
        clients[i]->cmd = NULL;
        clients[i]->logged = 0;
        clients[i]->uuid = NULL;
        clients[i]->name = NULL;
    }
    return clients;
}

int launch_server(int port)
{
    core_t core;
    client_t **clts = init_clients();
    int sv_sock = set_server_socket(port, clts[0]);

    if (sv_sock == -1)
        return 84;
    TAILQ_INIT(&core.teams_head);
    FD_ZERO(&core.fd_sets.r_fds_save);
    FD_ZERO(&core.fd_sets.w_fds_save);
    FD_SET(sv_sock, &core.fd_sets.r_fds_save);
    run_server(&core, clts, sv_sock);
    return 0;
}
