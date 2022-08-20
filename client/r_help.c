/*
** EPITECH PROJECT, 2022
** r_help.c
** File description:
** r_help
*/

#include "client.h"

bool r_help(res_t *pckg, char **uuid)
{
    (void)uuid;
    write(1, pckg->help.buffer, strlen(pckg->help.buffer));
    return false;
}
