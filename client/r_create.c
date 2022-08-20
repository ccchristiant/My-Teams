/*
** EPITECH PROJECT, 2022
** r_create.c
** File description:
** r_create
*/

#include "client.h"

void r_create_team(res_t *pckg, char **uuid)
{
    if (strcmp(pckg->team.user_uuid, *uuid) == 0) {
        client_print_team_created(pckg->team.team_uuid,
        pckg->team.team_name, pckg->team.team_description);
    }
    client_event_team_created(pckg->team.team_uuid,
    pckg->team.team_name, pckg->team.team_description);
}

void r_create_channel(res_t *pckg, char **uuid)
{
    if (strcmp(pckg->channel.user_uuid, *uuid) == 0) {
        client_print_channel_created(pckg->channel.channel_uuid,
        pckg->channel.channel_name, pckg->channel.channel_description);
    }
    client_event_channel_created(pckg->channel.channel_uuid,
    pckg->channel.channel_name, pckg->channel.channel_description);
}

void r_create_thread(res_t *pckg, char **uuid)
{
    if (strcmp(pckg->thread.user_uuid, *uuid) == 0) {
        client_print_thread_created(pckg->thread.thread_uuid,
        pckg->thread.user_uuid, pckg->thread.thread_timestamp,
        pckg->thread.thread_title, pckg->thread.thread_body);
    }
    client_event_thread_created(pckg->thread.thread_uuid,
    pckg->thread.user_uuid, pckg->thread.thread_timestamp,
    pckg->thread.thread_title, pckg->thread.thread_body);
}

void r_create_reply(res_t *pckg, char **uuid)
{
    if (strcmp(pckg->reply.user_uuid, *uuid) == 0) {
        client_print_reply_created(pckg->reply.thread_uuid,
        pckg->reply.user_uuid, pckg->reply.reply_timestamp,
        pckg->reply.reply_body);
    }
    client_event_thread_reply_received(pckg->reply.team_uuid,
    pckg->reply.thread_uuid, pckg->reply.user_uuid,
    pckg->reply.reply_body);
}

bool r_create(res_t *pckg, char **uuid)
{
    switch (pckg->context) {
        case TEAM:
            r_create_team(pckg, uuid);
            break;
        case CHANNEL:
            r_create_channel(pckg, uuid);
            break;
        case THREAD:
            r_create_thread(pckg, uuid);
            break;
        default:
            r_create_reply(pckg, uuid);
    }
    return false;
}
