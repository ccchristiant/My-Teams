/*
** EPITECH PROJECT, 2022
** info_sub.c
** File description:
** info_sub
*/

#include "server.h"

void info_thread(client_t **clts, int fd)
{
    res_t pckg;

    pckg.command = 13;
    pckg.context = THREAD;
    strcpy(pckg.thread.thread_uuid, clts[fd]->thread->thread_uuid);
    strcpy(pckg.thread.user_uuid, clts[fd]->thread->user_uuid);
    pckg.thread.thread_timestamp = clts[fd]->thread->timestamp;
    strcpy(pckg.thread.thread_title, clts[fd]->thread->thread_title);
    strcpy(pckg.thread.thread_body, clts[fd]->thread->thread_body);
    write(fd, &pckg, sizeof(res_t));
}

void info_channel(client_t **clts, int fd)
{
    res_t pckg;

    pckg.command = 13;
    pckg.context = CHANNEL;
    strcpy(pckg.channel.channel_uuid, clts[fd]->channel->channel_uuid);
    strcpy(pckg.channel.channel_name, clts[fd]->channel->channel_name);
    strcpy(pckg.channel.channel_description, clts[fd]->channel->channel_description);
    write(fd, &pckg, sizeof(res_t));
}

void info_team(client_t **clts, int fd)
{
    res_t pckg;

    pckg.command = 13;
    pckg.context = TEAM;
    strcpy(pckg.team.team_uuid, clts[fd]->team->team_uuid);
    strcpy(pckg.team.team_name, clts[fd]->team->team_name);
    strcpy(pckg.team.team_description, clts[fd]->team->team_description);
    write(fd, &pckg, sizeof(res_t));
}

void info_user(client_t **clts, int fd)
{
    res_t pckg;

    pckg.command = 13;
    pckg.context = USER;
    strcpy(pckg.user.user_uuid, clts[fd]->uuid);
    strcpy(pckg.user.user_name, clts[fd]->name);
    pckg.user.user_status = clts[fd]->logged;
    write(fd, &pckg, sizeof(res_t));
}
