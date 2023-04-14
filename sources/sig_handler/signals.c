/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afavre <afavre@student.42lausanne.ch>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/06 09:57:14 by afavre            #+#    #+#             */
/*   Updated: 2023/04/06 09:57:17 by afavre           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void	handler(int sig, siginfo_t *info, void *context)
{
	t_data *data = (t_data *)info;

	(void)context;
	//ft_printf("sig_state -> %d\n", data->sig_state);
	if (data->sig_state == 0)
	{
		if (sig == SIGINT)
		{
			write(1, "\n", 1);
			rl_replace_line("", 0);
			rl_on_new_line();
			rl_redisplay();
		}
	}
}

void sig_handler(t_data *data) {
	struct sigaction sa;
	union sigval value;

	memset(&sa, 0, sizeof(sa));
	value.sival_ptr = data;
	sa.sa_flags = SA_SIGINFO;
	sa.sa_sigaction = handler;
	sigaction(SIGINT, &sa, NULL);
}
