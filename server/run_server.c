/*
** EPITECH PROJECT, 2022
** run_server.c
** File description:
** run_server
*/

#include "server.h"

void reset_fds_and_buf(core_t *core, char *buf)
{
    core->fd_sets.r_fds = core->fd_sets.r_fds_save;
    core->fd_sets.w_fds = core->fd_sets.w_fds_save;
    select(FD_SETSIZE, &core->fd_sets.r_fds, &core->fd_sets.w_fds, NULL, NULL);
    memset(buf, 0, TOT_LEN);
}

void fd_setter(core_t *core, client_t **clts, int fd)
{
    FD_SET(clts[fd]->cl_sock, &core->fd_sets.r_fds_save);
    FD_SET(clts[fd]->cl_sock, &core->fd_sets.w_fds_save);
}

void fd_clearer(core_t *core, client_t **clts, int fd)
{
    FD_CLR(clts[fd]->cl_sock, &core->fd_sets.r_fds_save);
    FD_CLR(clts[fd]->cl_sock, &core->fd_sets.w_fds_save);
}

void run_server(core_t *core, client_t **clts, int sv_sock)
{
    char buf[TOT_LEN];

    while (true) {
        reset_fds_and_buf(core, buf);
        for (int fd = 0; fd < FD_SETSIZE; fd++) {
            if (FD_ISSET(fd, &core->fd_sets.r_fds)) {
                if (fd == sv_sock) {
                    accept_client(clts[fd], sv_sock);
                    fd_setter(core, clts, fd);
                } else
                    read(fd, buf, TOT_LEN);
            }
            if (FD_ISSET(fd, &core->fd_sets.w_fds)) {
                if (manage_client(core, clts, fd, buf)) {
                    fd_clearer(core, clts, fd);
                    close(fd);
                }
                memset(buf, 0, sizeof(buf));
            }
        }
    }
}
