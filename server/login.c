/*
** EPITECH PROJECT, 2022
** login.c
** File description:
** login
*/

#include "server.h"

void set_uuid(client_t **clts, int fd)
{
    uuid_t uuid;

    uuid_generate(uuid);
    uuid_unparse(uuid, clts[fd]->uuid);
}

void send_login_res(client_t **clts, int fd)
{
    res_t pckg;

    pckg.command = 1;
    strcpy(pckg.login.user_uuid, clts[fd]->uuid);
    strcpy(pckg.login.user_name, clts[fd]->name);
    for (int i = 0; i < FD_SETSIZE; i++)
        if (clts[i]->name != NULL && clts[i]->logged == 1)
            write(i, &pckg, sizeof(res_t));
}

bool check_existence(client_t **clts, int fd, char *name)
{
    for (int i = 0; i < FD_SETSIZE; i++)
        if (clts[i]->name != NULL && strcmp(clts[i]->name, name) == 0) {
            clts[fd] = clts[i];
            clts[fd]->cl_sock = fd;
            clts[fd]->logged = 1;
            server_event_user_logged_in(clts[fd]->uuid);
            send_login_res(clts, fd);
            return true;
        }
    return false;
}

bool login(core_t *core, client_t **clts, int fd, char **args)
{
    (void)core;
    if (args != NULL && clts[fd]->name == NULL &&
        !check_existence(clts, fd, args[0])) {
        clts[fd]->cl_sock = fd;
        clts[fd]->logged = 1;
        clts[fd]->uuid = malloc(sizeof(char) * UUID_LENGTH);
        set_uuid(clts, fd);
        clts[fd]->name = strdup(args[0]);
        clts[fd]->tmp_team = NULL;
        clts[fd]->team = NULL;
        clts[fd]->tmp_channel = NULL;
        clts[fd]->channel = NULL;
        clts[fd]->tmp_thread = NULL;
        clts[fd]->thread = NULL;
        TAILQ_INIT(&clts[fd]->messages_head);
        server_event_user_created(clts[fd]->uuid, clts[fd]->name);
        server_event_user_logged_in(clts[fd]->uuid);
        send_login_res(clts, fd);
    }
    return false;
}
