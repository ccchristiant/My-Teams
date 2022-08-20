/*
** EPITECH PROJECT, 2022
** r_users.c
** File description:
** r_users
*/

#include "client.h"

bool r_users(res_t *pckg, char **uuid)
{
    (void)uuid;
    for (int i = 0; i < pckg->users.nb; i++) {
        client_print_users(pckg->users.users[i].user_uuid,
        pckg->users.users[i].user_name, pckg->users.users[i].user_status);
    }
    return false;
}
