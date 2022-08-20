/*
** EPITECH PROJECT, 2022
** manage_client.c
** File description:
** manage_client
*/

#include "server.h"

static const command_t cmds[] = {
    {"0", 1, &help},
    {"1", 1, &login},
    {"2", 1, &logout},
    {"3", 1, &users},
    {"4", 1, &user},
    {"5", 1, &send_msg},
    {"6", 1, &messages},
    {"7", 1, &subscribe},
    {"8", 1, &subscribed},
    {"9", 1, &unsubscribe},
    {"10", 2, &use},
    {"11", 2, &create},
    {"12", 2, &list},
    {"13", 2, &info},
};

int nb_db_quotes(char *cmd)
{
    int nb = 0;

    for (int i = 0; cmd[i] != '\0'; i++)
        nb += (cmd[i] == '\"');
    return nb;
}

bool fill_args(char *clean_cmd, char ***args)
{
    int j = 0;
    int k = 0;

    for (int i = 0; clean_cmd[i] != '\0'; i += 1) {
        if (strncmp(&clean_cmd[i], " ", 1) != 0 &&
            strncmp(&clean_cmd[i], "\"", 1) != 0)
            return true;
        j = 0;
        if (strncmp(&clean_cmd[i], "\"", 1) == 0) {
            i += 1;
            for (; clean_cmd[i + j] != '\"'; j++);
            (*args)[k] = malloc(sizeof(char) * (j + 1));
            (*args)[k] = strncpy((*args)[k], &clean_cmd[i], j);
            (*args)[k][j] = '\0';
            k += 1;
            i += j;
            if (clean_cmd[i + 1] != ' ' && clean_cmd[i + 1] != '\0')
                return true;
        }
    }
    return false;
}

bool get_arguments(char *cmd, char ***args)
{
    char *cmd_without_newline = strtok(cmd, "\r\n\0");
    char *clean_cmd;
    int st = 0;
    int nb_db_quotes_res;

    if (cmd_without_newline == NULL) {
        *args = NULL;
        return false;
    }
    for (; cmd_without_newline[st] == ' '; st++);
    if (st == 0)
        return true;
    clean_cmd = strdup(&cmd_without_newline[st]);
    nb_db_quotes_res = nb_db_quotes(clean_cmd);
    if (strlen(clean_cmd) == 2 || nb_db_quotes_res == 0 ||
        nb_db_quotes_res % 2 != 0)
        return true;
    return fill_args(clean_cmd, args);
}

bool exec_command(core_t *core, client_t **clts, int fd, char *cmd)
{
    char **args;

    printf("Received command: `%s`\n", cmd);
    for (int i = 13; i >= 0; i--) {
        if (strncmp(cmd, cmds[i].nm, cmds[i].ln) == 0) {
            if (i > 1 && clts[fd]->logged == 0) {
                send_error(fd, UNAUTHORIZED, NULL);
                return false;
            }
            args = malloc(sizeof(char *) * 4);
            memset(args, 0, sizeof(char *) * 4);
            if (get_arguments(&cmd[cmds[i].ln], &args))
                return false;
            if ((*cmds[i].f) (core, clts, fd, args))
                return true;
            return false;
        }
    }
    printf("Command not found\n");
    return false;
}

bool manage_client(core_t *core, client_t **clts, int fd, char *buf)
{
    if (strlen(buf) == 0)
        return 0;
    if (clts[fd]->tmp == NULL) {
        clts[fd]->tmp = malloc(sizeof(char) * TOT_LEN);
        memset(clts[fd]->tmp, 0, TOT_LEN);
    }
    if (clts[fd]->cmd == NULL) {
        clts[fd]->cmd = malloc(sizeof(char) * TOT_LEN);
        memset(clts[fd]->cmd, 0, TOT_LEN);
    }
    clts[fd]->tmp = strcat(clts[fd]->tmp, buf);
    while (strchr(clts[fd]->tmp, '\n')) {
        strncpy(clts[fd]->cmd, clts[fd]->tmp, af_ret(clts[fd]->tmp) - clts[fd]->tmp);
        if (exec_command(core, clts, fd, clts[fd]->cmd))
            return true;
        memset(clts[fd]->cmd, 0, TOT_LEN);
        if (strchr(clts[fd]->tmp, '\n') != NULL)
            clts[fd]->tmp = strcpy(clts[fd]->tmp, af_ret(clts[fd]->tmp));
    }
    return false;
}
