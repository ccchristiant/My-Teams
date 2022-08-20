/*
** EPITECH PROJECT, 2022
** r_user.c
** File description:
** r_user
*/

#include "client.h"

bool r_user(res_t *pckg, char **uuid)
{
    (void)uuid;
    client_print_user(pckg->user.user_uuid, pckg->user.user_name,
    pckg->user.user_status);
    return false;
}
