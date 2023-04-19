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

static void	handler(int sig)
{
	if (g_glob.status == 0)
	{
		if (sig == SIGINT)
		{
			ft_putchar('\n');
			rl_replace_line("", 0);
			rl_on_new_line();
			rl_redisplay();
		}
		if (sig == SIGQUIT)
		{
			signal(SIGQUIT, SIG_IGN);
		}
	}
	if (g_glob.status == 1)
	{
		if (sig == SIGINT)
			ft_putchar('\n');
		if (sig == SIGQUIT)
			ft_printf("Quit: 3\n");
		g_glob.status = 0;
	}
}

void sig_handler() {
	struct sigaction sa_int;

	sa_int.sa_handler = &handler;
	sigaction(SIGINT, &sa_int, NULL);
	sigaction(SIGQUIT, &sa_int, NULL);
}
