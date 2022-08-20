/*
** EPITECH PROJECT, 2022
** r_info.c
** File description:
** r_info
*/

#include "client.h"

void r_info_team(res_t *pckg)
{
    client_print_team(pckg->team.team_uuid, pckg->team.team_name,
    pckg->team.team_description);
}

void r_info_channel(res_t *pckg)
{
    client_print_channel(pckg->channel.channel_uuid,
    pckg->channel.channel_name, pckg->channel.channel_description);
}

void r_info_thread(res_t *pckg)
{
    client_print_thread(pckg->thread.thread_uuid, pckg->thread.user_uuid,
    pckg->thread.thread_timestamp, pckg->thread.thread_title,
    pckg->thread.thread_body);
}

void r_info_user(res_t *pckg)
{
    client_print_user(pckg->user.user_uuid, pckg->user.user_name,
    pckg->user.user_status);
}

bool r_info(res_t *pckg, char **uuid)
{
    (void)uuid;
    switch (pckg->context) {
        case TEAM:
            r_info_team(pckg);
            break;
        case CHANNEL:
            r_info_channel(pckg);
            break;
        case THREAD:
            r_info_thread(pckg);
            break;
        default:
            r_info_user(pckg);
    }
    return false;
}
