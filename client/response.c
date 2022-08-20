/*
** EPITECH PROJECT, 2022
** response.c
** File description:
** response
*/

#include "client.h"

static const response_t r_cmds[] = {
    {0, &r_help},
    {1, &r_login},
    {2, &r_logout},
    {3, &r_users},
    {4, &r_user},
    {5, &r_send},
    {6, &r_messages},
    {7, &r_subscribe},
    {8, &r_subscribed},
    {9, &r_unsubscribe},
    {10, &r_use},
    {11, &r_create},
    {12, &r_list},
    {13, &r_info},
    {14, &r_error}
};

bool response(int sv_sock, char **uuid)
{
    res_t pckg;

    read(sv_sock, &pckg, sizeof(res_t));
    for (int i = 0; i < 15; i++)
        if (pckg.command == i) {
            if ((*r_cmds[i].g) (&pckg, uuid))
                return true;
            return false;
        }
    return false;
}
