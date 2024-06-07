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

#include <signal.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

volatile sig_atomic_t	ack_received = 0;
volatile sig_atomic_t	msg_received = 0;

void	ack_handler(int signal)
{
	ack_received = 1;
}

void	msg_handler(int signal)
{
	msg_received = 1;
}

void	send_signal(int server_pid, char *message)
{
	int	i;
	int	bit;

	i = 0;
	while (message[i] != '\0')
	{
		bit = 7;
		while (bit >= 0)
		{
			ack_received = 0;
			if (message[i] & (1 << bit))
			{
				kill(server_pid, SIGUSR1);
			}
			else
			{
				kill(server_pid, SIGUSR2);
			}
			while (!ack_received)
			{
				usleep(100); // Wait for acknowledgment
			}
			bit--;
		}
		i++;
	}
	// Send null character to signal end of message
	bit = 7;
	while (bit >= 0)
	{
		ack_received = 0;
		kill(server_pid, SIGUSR2);
		while (!ack_received)
		{
			usleep(100); // Wait for acknowledgment
		}
		bit--;
	}
}

int	main(int argc, char *argv[])
{
	pid_t				server_pid;
	char				*message;
	struct sigaction	ack_action;
	struct sigaction	msg_action;

	if (argc != 3)
	{
		fprintf(stderr, "Usage: %s <server_pid> <message>\n", argv[0]);
		return (1);
	}
	server_pid = (pid_t)atoi(argv[1]);
	message = argv[2];
	ack_action.sa_handler = &ack_handler;
	sigemptyset(&ack_action.sa_mask);
	ack_action.sa_flags = 0;
	if (sigaction(SIGUSR1, &ack_action, NULL) == -1)
	{
		perror("sigaction");
		return (1);
	}
	msg_action.sa_handler = &msg_handler;
	sigemptyset(&msg_action.sa_mask);
	msg_action.sa_flags = 0;
	if (sigaction(SIGUSR2, &msg_action, NULL) == -1)
	{
		perror("sigaction");
		return (1);
	}
	send_signal(server_pid, message);
	// Wait for the message received acknowledgment from the server
	while (!msg_received)
	{
		pause();
	}
	printf("Message reçu\n");
	return (0);
}
