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

void    sig_handler(int signal)
{
    int     bit;

    if (signal == SIGUSR1)
        printf("\nSIGUSR1\n");
    else
        printf("\nSIGUSR2\n");
}

int main(void)
{
    struct sigaction    action;

    printf("%d\n", getpid());
    action.sa_handler = &sig_handler;
    sigemptyset(&action.sa_mask);
    sigaction(SIGUSR1, &action, NULL);
    sigaction(SIGUSR2, &action, NULL);
    while(1)
        pause();
    return (0);
}
