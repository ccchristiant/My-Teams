/*
** EPITECH PROJECT, 2022
** myteams server
** File description:
** myteams server
*/

#include "server.h"

int error_handling(int ac, char **av)
{
    if (ac != 2) {
        printf("USAGE: ./myteams_server port\n\n\tport\t");
        printf("is the port number on which the server socket listens\n");
        return 84;
    }
    if (ac == 2 && strcmp(av[1], "-help") == 0) {
        printf("USAGE: ./myteams_server port\n\n\tport\t");
        printf("is the port number on which the server socket listens\n");
        return 1;
    }
    return 0;
}

int main(int ac, char **av)
{
    int res;

    setvbuf(stdout, NULL, _IONBF, 0);
    res = error_handling(ac, av);
    if (res == 84)
        return res;
    if (res == 1)
        return 0;
    return launch_server(atoi(av[1]));
}
