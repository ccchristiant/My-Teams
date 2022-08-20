/*
** EPITECH PROJECT, 2022
** send_error.c
** File description:
** send_error
*/

#include "server.h"

void send_error(int fd, error_type_t type, char *uuid)
{
    res_t pckg;

    pckg.command = 14;
    pckg.error.type = type;
    if (type == UNKNOWN_TEAM || type == UNKNOWN_CHANNEL ||
        type == UNKNOWN_THREAD || type == UNKNOWN_USER)
        strcpy(pckg.error.uuid, uuid);
    write(fd, &pckg, sizeof(res_t));
}
