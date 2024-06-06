/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sranaivo <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/06 10:30:53 by sranaivo          #+#    #+#             */
/*   Updated: 2024/06/06 10:30:55 by sranaivo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minitalk.h"
#include <stdio.h>

void    send_signal(int server_pid, char *message)
{
    int i;
    int bit;

    i = -1;
    while (message[++i])
    {
        bit = 7;
        while (bit >= 0)
        {
            if (message[i] & (1 << bit))
                kill(server_pid, SIGUSR1);
            else
                kill(server_pid, SIGUSR2);
            usleep(50);
            bit--;
        }
    }
}

int main(int argc,char *argv[])
{
    pid_t   server_pid;
    char    *message;

    server_pid = (pid_t)atoi(argv[1]);
    message = argv[2];
    printf("Client PID: %d\n", getpid());

    send_signal(server_pid, message);
    
    return (0);
}