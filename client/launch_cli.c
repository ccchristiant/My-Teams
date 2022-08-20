/*
** EPITECH PROJECT, 2022
** launch_cli.c
** File description:
** launch_cli
*/

#include "client.h"

static volatile int fd_to_close;

int set_server_socket(void)
{
    int sv_sock = socket(AF_INET, SOCK_STREAM, 0);

    if (sv_sock == -1) {
        perror("socket");
        return -1;
    }
    return sv_sock;
}

int set_client_socket(const char *ip, int port, int sv_sock)
{
    SOCKADDR_IN cl_sa_in;
    int cl_sock;
    char *res = malloc(sizeof(char) * 1024);

    cl_sa_in.sin_family = AF_INET;
    cl_sa_in.sin_port = htons(port);
    if (inet_pton(AF_INET, ip, &cl_sa_in.sin_addr) <= 0) {
        perror("inet_pton");
        return -1;
    }
    cl_sock = connect(sv_sock, (SOCKADDR*)&cl_sa_in, sizeof(cl_sa_in));
    if (cl_sock == -1) {
        perror("connect");
        return -1;
    }
    memset(res, 0, 1024);
    read(sv_sock, res, 1024);
    write(1, res, strlen(res));
    write(sv_sock, "Connected\n", 11);
    return cl_sock;
}

void force_shutdown(int signum)
{
    (void)signum;
    close(fd_to_close);
    exit(0);
}

int launch_cli(const char *ip, int port)
{
    int sv_sock = set_server_socket();
    int cl_sock;
    fd_sets_t fd_sets;

    signal(SIGINT, force_shutdown);
    if (sv_sock == -1)
        return 84;
    cl_sock = set_client_socket(ip, port, sv_sock);
    fd_to_close = cl_sock;
    if (cl_sock == -1)
        return 84;
    FD_ZERO(&fd_sets.r_fds_save);
    FD_ZERO(&fd_sets.w_fds_save);
    FD_SET(0, &fd_sets.r_fds_save);
    FD_SET(sv_sock, &fd_sets.r_fds_save);
    FD_SET(sv_sock, &fd_sets.w_fds_save);
    run_cli(&fd_sets, sv_sock);
    close(cl_sock);
    return 0;
}
