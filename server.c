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

void	print_list(t_list *lst)
{
	t_list	*temp;

	temp = lst;
	while (temp)
	{
		printf("%c", *(char *)(temp->content));
		temp = temp->next;
	}
}

void	sig_handler(int signal, siginfo_t *info, void *context)
{
	static t_list			*str = NULL;
	static unsigned char	c = 0;
	static int				bit = 7;
	char					*char_node;
	t_list					*new_node;

	if (signal == SIGUSR1)
		c |= (1 << bit);
	bit--;
	if (bit < 0)
	{
		if (c == '\0')
		{
			print_list(str);
			printf("\n");
			ft_lstclear(&str, free);
			kill(info->si_pid, SIGUSR2);
		}
		char_node = malloc(sizeof(char));
		*char_node = c;
		new_node = ft_lstnew(char_node);
		ft_lstadd_back(&str, new_node);
		c = 0;
		bit = 7;
	}
	kill(info->si_pid, SIGUSR1);
}

int	main(void)
{
	struct sigaction	action;

	printf("Server PID: %d\n", getpid());
	action.sa_sigaction = &sig_handler;
	sigemptyset(&action.sa_mask);
	action.sa_flags = SA_SIGINFO;
	sigaction(SIGUSR1, &action, NULL);
	sigaction(SIGUSR2, &action, NULL);
	while (1)
	{
		pause();
	}
	return (0);
}
