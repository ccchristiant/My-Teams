/*
** EPITECH PROJECT, 2022
** protocol.c
** File description:
** protocol
*/

#include "client.h"

static const protocol_t p_cmds[] = {
    {"/help", 5, "0\n"},
    {"/login", 6, "1"},
    {"/logout", 7, "2\n"},
    {"/users", 6, "3\n"},
    {"/user", 5, "4"},
    {"/send", 5, "5"},
    {"/messages", 9, "6"},
    {"/subscribed", 11, "8"},
    {"/subscribe", 10, "7"},
    {"/unsubscribe", 12, "9"},
    {"/use", 4, "10"},
    {"/create", 7, "11"},
    {"/list", 5, "12\n"},
    {"/info", 5, "13\n"}
};

void send_ptc(int fd, char *code, char *args)
{
    char *res;

    if (strchr(code, '\n'))
        write(fd, code, strlen(code));
    else {
        res = concat(code, args);
        write(fd, res, strlen(res));
    }
}

void protocol(int sv_sock, char *buf, char **tmp, char **cmd)
{
    if (strlen(buf) == 0)
        return;
    *tmp = strcat(*tmp, buf);
    while (strchr(*tmp, '\n')) {
        strncpy(*cmd, *tmp, af_ret(*tmp) - *tmp);
        for (int i = 0; i < 14; i++)
            if (strncmp(*cmd, p_cmds[i].nm, p_cmds[i].ln) == 0) {
                send_ptc(sv_sock, p_cmds[i].cd, &(*cmd)[p_cmds[i].ln]);
                break;
            }
        memset(*cmd, 0, TOT_LEN);
        *tmp = strcpy(*tmp, af_ret(*tmp));
    }
}
