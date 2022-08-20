/*
** EPITECH PROJECT, 2022
** accept_client.c
** File description:
** accept_client
*/

#include "server.h"

void accept_client(client_t *clt, int sv_sock)
{
    clt->cl_sa_size = sizeof(clt->cl_sa_in);
    clt->cl_sock = accept(sv_sock, (SOCKADDR*)&clt->cl_sa_in, (socklen_t*)&clt->cl_sa_size);
    write(clt->cl_sock, "Hello\r\n", 7);
}
