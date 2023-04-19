/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lorobert <marvin@42lausanne.ch>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/06 09:57:14 by afavre            #+#    #+#             */
/*   Updated: 2023/04/19 10:07:40 by lorobert         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void	handler(int sig, siginfo_t *info, void *context)
{
	(void)info;
	(void)context;
	if (g_glob.status == 0)
	{
		if (sig == SIGINT)
		{
			write(1, "\n", 1);
			rl_replace_line("", 0);
			rl_on_new_line();
			rl_redisplay();
		}
	}
	if (g_glob.status == 1)
	{
		if (sig == SIGINT)
		{
			ft_putchar('\n');
		}
		if (sig == SIGQUIT)
		{
			ft_printf("Quit: 3\n");
		}
		g_glob.status = 0;
	}
}

void sig_handler() {
	struct sigaction sa;

	sa.sa_flags = SA_SIGINFO;
	sa.sa_sigaction = handler;
	sigaction(SIGINT, &sa, NULL);
	sigaction(SIGQUIT, &sa, NULL);
}
