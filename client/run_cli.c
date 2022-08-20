/*
** EPITECH PROJECT, 2022
** run_cli.c
** File description:
** run_cli
*/

#include "client.h"

void run_cli(fd_sets_t *fd_sets, int sv_sock)
{
    char *buf = malloc(sizeof(char) * TOT_LEN);
    char *tmp = malloc(sizeof(char) * TOT_LEN);
    char *cmd = malloc(sizeof(char) * TOT_LEN);
    char *uuid = NULL;

    memset(tmp, 0, TOT_LEN);
    memset(cmd, 0, TOT_LEN);
    while (true) {
        fd_sets->r_fds = fd_sets->r_fds_save;
        fd_sets->w_fds = fd_sets->w_fds_save;
        select(FD_SETSIZE, &fd_sets->r_fds, &fd_sets->w_fds, NULL, NULL);
        memset(buf, 0, TOT_LEN);
        if (FD_ISSET(0, &fd_sets->r_fds))
            read(0, buf, TOT_LEN);
        if (FD_ISSET(sv_sock, &fd_sets->w_fds))
            protocol(sv_sock, buf, &tmp, &cmd);
        if (FD_ISSET(sv_sock, &fd_sets->r_fds))
            if (response(sv_sock, &uuid))
                return;
    }
}
