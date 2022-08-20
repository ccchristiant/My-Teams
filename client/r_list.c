/*
** EPITECH PROJECT, 2022
** r_list.c
** File description:
** r_list
*/

#include "client.h"

void r_list_team(res_t *pckg)
{
    client_print_teams(pckg->team.team_uuid, pckg->team.team_name,
    pckg->team.team_description);
}

void r_list_channel(res_t *pckg)
{
    client_team_print_channels(pckg->channel.channel_uuid,
    pckg->channel.channel_name, pckg->channel.channel_description);
}

void r_list_thread(res_t *pckg)
{
    client_channel_print_threads(pckg->thread.thread_uuid,
    pckg->thread.user_uuid, pckg->thread.thread_timestamp,
    pckg->thread.thread_title, pckg->thread.thread_body);
}

void r_list_reply(res_t *pckg)
{
    client_thread_print_replies(pckg->reply.thread_uuid,
    pckg->reply.user_uuid, pckg->reply.reply_timestamp,
    pckg->reply.reply_body);
}

bool r_list(res_t *pckg, char **uuid)
{
    (void)uuid;
    switch (pckg->context) {
        case TEAM:
            r_list_team(pckg);
            break;
        case CHANNEL:
            r_list_channel(pckg);
            break;
        case THREAD:
            r_list_thread(pckg);
            break;
        default:
            r_list_reply(pckg);
    }
    return false;
}
