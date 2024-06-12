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

void	print_free_list(t_list **lst)
{
	t_list	*temp;

	temp = *lst;
	ft_printf("New message: ");
	while (temp)
	{
		ft_printf("%c", *(char *)(temp->content));
		temp = temp->next;
	}
	ft_lstclear(lst, free);
	ft_printf("\n");
}

static void	sig_handler(int signal, siginfo_t *info, void *context)
{
	static t_list			*str = NULL;
	static unsigned char	c = 0;
	static int				bit = 7;
	char					*char_ptr;
	t_list					*new_node;

	(void)context;
	if (signal == SIGUSR1)
		c |= (1 << bit);
	bit--;
	if (bit < 0)
	{
		if (c == '\0')
			print_free_list(&str);
		else
		{
			char_ptr = malloc(sizeof(char));
			*char_ptr = c;
			new_node = ft_lstnew(char_ptr);
			ft_lstadd_back(&str, new_node);
		}
		c = 0;
		bit = 7;
	}
	kill(info->si_pid, SIGUSR1);
}

int	main(void)
{
	struct sigaction	action;

	ft_printf("Server PID: <%d>\n", getpid());
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
