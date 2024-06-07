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

#include <signal.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

typedef struct s_list
{
	void			*content;
	struct s_list	*next;
}					t_list;

t_list	*ft_lstnew(void *content)
{
	t_list	*new;

	new = malloc(sizeof(t_list));
	if (!new)
		return (NULL);
	new->content = content;
	new->next = NULL;
	return (new);
}

void	ft_lstadd_back(t_list **lst, t_list *new)
{
	t_list	*temp;

	if (!lst || !new)
		return ;
	if (*lst == NULL)
	{
		*lst = new;
	}
	else
	{
		temp = *lst;
		while (temp->next)
			temp = temp->next;
		temp->next = new;
	}
}

void	ft_lstclear(t_list **lst)
{
	t_list	*temp;

	while (*lst)
	{
		temp = (*lst)->next;
		free((*lst)->content); // Free the content
		free(*lst);
		*lst = temp;
	}
}

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
	char					*char_ptr;
	t_list					*new_node;

	if (signal == SIGUSR1)
	{
		c |= (1 << bit);
	}
	else if (signal == SIGUSR2)
	{
		c &= ~(1 << bit);
	}
	bit--;
	if (bit < 0)
	{
		char_ptr = malloc(sizeof(char));
		*char_ptr = c;
		new_node = ft_lstnew(char_ptr);
		ft_lstadd_back(&str, new_node);
		if (c == '\0')
		{
			print_list(str);
			printf("\n");
			ft_lstclear(&str);
			// Send signal to client to indicate the message was received
			kill(info->si_pid, SIGUSR2);
		}
		c = 0;
		bit = 7;
	}
	// Send acknowledgment to client
	kill(info->si_pid, SIGUSR1);
}

int	main(void)
{
	struct sigaction	action;

	printf("Server PID: %d\n", getpid());
	action.sa_sigaction = &sig_handler;
	sigemptyset(&action.sa_mask);
	action.sa_flags = SA_SIGINFO;
	if (sigaction(SIGUSR1, &action, NULL) == -1)
	{
		perror("sigaction");
		return (1);
	}
	if (sigaction(SIGUSR2, &action, NULL) == -1)
	{
		perror("sigaction");
		return (1);
	}
	while (1)
	{
		pause();
	}
	return (0);
}
