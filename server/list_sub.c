/*
** EPITECH PROJECT, 2022
** list_sub.c
** File description:
** list_sub
*/

#include "server.h"

void list_reply(client_t **clts, int fd)
{
    reply_t *tmp_reply;

    TAILQ_FOREACH(tmp_reply, &clts[fd]->thread->replies_head, replies) {
        res_t pckg;
        pckg.command = 12;
        pckg.context = REPLY;
        strcpy(pckg.reply.team_uuid, tmp_reply->team_uuid);
        strcpy(pckg.reply.thread_uuid, tmp_reply->thread_uuid);
        strcpy(pckg.reply.user_uuid, tmp_reply->user_uuid);
        pckg.reply.reply_timestamp = tmp_reply->timestamp;
        strcpy(pckg.reply.reply_body, tmp_reply->reply_body);
        write(fd, &pckg, sizeof(res_t));
    }
}

void list_thread(client_t **clts, int fd)
{
    thread_t *tmp_thread;

    TAILQ_FOREACH(tmp_thread, &clts[fd]->channel->threads_head, threads) {
        res_t pckg;
        pckg.command = 12;
        pckg.context = THREAD;
        strcpy(pckg.thread.thread_uuid, tmp_thread->thread_uuid);
        strcpy(pckg.thread.user_uuid, tmp_thread->user_uuid);
        pckg.thread.thread_timestamp = tmp_thread->timestamp;
        strcpy(pckg.thread.thread_title, tmp_thread->thread_title);
        strcpy(pckg.thread.thread_body, tmp_thread->thread_body);
        write(fd, &pckg, sizeof(res_t));
    }
}

void list_channel(client_t **clts, int fd)
{
    channel_t *tmp_channel;

    TAILQ_FOREACH(tmp_channel, &clts[fd]->team->channels_head, channels) {
        res_t pckg;
        pckg.command = 12;
        pckg.context = CHANNEL;
        strcpy(pckg.channel.channel_uuid, tmp_channel->channel_uuid);
        strcpy(pckg.channel.channel_name, tmp_channel->channel_name);
        strcpy(pckg.channel.channel_description, tmp_channel->channel_description);
        write(fd, &pckg, sizeof(res_t));
    }
}

void list_team(core_t *core, int fd)
{
    team_t *tmp_team;

    TAILQ_FOREACH(tmp_team, &core->teams_head, teams) {
        res_t pckg;
        pckg.command = 12;
        pckg.context = TEAM;
        strcpy(pckg.team.team_uuid, tmp_team->team_uuid);
        strcpy(pckg.team.team_name, tmp_team->team_name);
        strcpy(pckg.team.team_description, tmp_team->team_description);
        write(fd, &pckg, sizeof(res_t));
    }
}
