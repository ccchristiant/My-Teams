/*
** EPITECH PROJECT, 2022
** myteams client
** File description:
** myteams client
*/

#include "client.h"

int error_handling(int ac, char **av)
{
    if (ac == 2 && strcmp(av[1], "-help") == 0) {
        printf("USAGE: ./myteams_cli ip port\n\n\tip\tis the server ip ");
        printf("address on which the server socket listens\n\nport\t");
        printf("is the port number on which the server socket listens\n");
        return 1;
    }
    if (ac != 3) {
        printf("USAGE: ./myteams_cli ip port\n\n\tip\tis the server ip ");
        printf("address on which the server socket listens\n\nport\t");
        printf("is the port number on which the server socket listens\n");
        return 84;
    }
    return 0;
}

int main(int ac, char **av)
{
    int res;

    res = error_handling(ac, av);
    if (res == 84)
        return res;
    if (res == 1)
        return 0;
    return launch_cli(av[1], atoi(av[2]));
}