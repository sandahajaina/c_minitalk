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

volatile sig_atomic_t	g_sig_received = 0;

static void	sig_received_handler(int signal)
{
	(void) signal;
	g_sig_received = 1;
}

static void	send_char(pid_t server_pid, char c)
{
	int	bit;

	bit = 7;
	while (bit >= 0)
	{
		g_sig_received = 0;
		if (c & (1 << bit))
			kill(server_pid, SIGUSR1);
		else
			kill(server_pid, SIGUSR2);
		while (g_sig_received != 1)
		{
			usleep(100);
		}
		bit--;
	}
}

static void	send_signal(int server_pid, char *message)
{
	int	i;

	i = -1;
	while (message[++i])
		send_char(server_pid, message[i]);
	send_char(server_pid, '\0');
}

int	main(int argc, char *argv[])
{
	pid_t				server_pid;
	char				*message;
	struct sigaction	action;

	if (argc != 3)
	{
		ft_printf("Usage: %s <server_pid> <message>\n", argv[0]);
		return (1);
	}
	server_pid = (pid_t)atoi(argv[1]);
	message = argv[2];
	action.sa_handler = &sig_received_handler;
	sigemptyset(&action.sa_mask);
	action.sa_flags = 0;
	sigaction(SIGUSR1, &action, NULL);
	sigaction(SIGUSR2, &action, NULL);
	send_signal(server_pid, message);
	return (0);
}
