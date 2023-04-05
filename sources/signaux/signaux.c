/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signaux.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afavre <afavre@student.42lausanne.ch>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/04 12:54:07 by afavre            #+#    #+#             */
/*   Updated: 2023/04/04 12:54:09 by afavre           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void	sigint_handler(int signum) {
	if (signum == SIGINT) {
		printf("SIGINT");
	}
}

int sig() {
	struct termios tp;
	struct sigaction sa;

	tcgetattr(STDIN_FILENO, &tp);
	tp.c_lflag &= ISIG;
	tcsetattr(STDIN_FILENO, TCSANOW, &tp);
	sa.sa_handler = sigint_handler;
	sigemptyset(&sa.sa_mask);
	sa.sa_flags = SA_RESTART;
	sigaction(SIGQUIT, &sa, NULL);
	return 0;
}
