/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afavre <afavre@42lausanne.ch>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/06 09:57:14 by afavre            #+#    #+#             */
/*   Updated: 2023/04/24 09:40:16 by lorobert         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

static void	handler(int sig)
{
	if (g_glob.status == 0)
	{
		if (sig == SIGINT)
		{
			write(1, "\n", 1);
			rl_replace_line("", 0);
			rl_on_new_line();
			rl_redisplay();
		}
		if (sig == SIGQUIT)
		{
			rl_redisplay();
			return ;
		}
	}
	if (g_glob.status == 1)
	{
		if (sig == SIGINT)
			write(1, "\n", 1);
		if (sig == SIGQUIT)
			ft_printf("Quit: 3\n");
		g_glob.status = 0;
	}
}

void	sig_handler(t_data *data)
{
	struct sigaction	sa_int;

	sa_int.sa_handler = &handler;
	if (sigaction(SIGINT, &sa_int, &data->old_sa) == -1)
		ft_printf("error sigint");
	if (sigaction(SIGQUIT, &sa_int, &data->old_sa) == -1)
		ft_printf("error sigquit");
}
