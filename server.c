/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sranaivo <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/04 09:30:10 by sranaivo          #+#    #+#             */
/*   Updated: 2024/06/04 09:30:13 by sranaivo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minitalk.h"
#include <stdio.h>
#include <string.h>

void    s_sig_handler(int signal, siginfo_t *info, void *x)
{
    t_list                  *str;
    static unsigned char    c = 0;
    static int              bit = 7;

    if (signal == SIGUSR1)
    {
        c |= (1 << bit);
    }
    printf("client: %d", info->si_pid);
    bit--;
    if (bit < 0)
    {
        write(1, &c, 1);
        c = 0;
        bit = 7;
    }
}

void sig_handler(int signal, siginfo_t *info, void *context)
{
    t_list                  *str;
    static unsigned char    c = 0;
    static int              bit = 7;

    if (signal == SIGUSR1) {
        c |= (1 << bit);
    }
    bit--;
    if (bit < 0)
    {
        write(1, &c, 1);
        c = 0;
        bit = 7;
    }
}

int main(void)
{
    struct sigaction    action;

    printf("Server PID: %d\n", getpid());
    action.sa_sigaction = &sig_handler;
    sigemptyset(&action.sa_mask);
    action.sa_flags = SA_SIGINFO;

    // if (sigaction(SIGUSR1, &action, NULL) == -1) {
    //     return 1;
    // }
    // if (sigaction(SIGUSR2, &action, NULL) == -1) {
    //     return 1;
    // }
    sigaction(SIGUSR1, &action, NULL);
    sigaction(SIGUSR2, &action, NULL);

    while(1)
        pause();
    return (0);
}
