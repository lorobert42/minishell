/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lorobert <marvin@42lausanne.ch>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/31 11:22:27 by afavre            #+#    #+#             */
/*   Updated: 2023/05/04 10:56:50 by lorobert         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void	fatal_error(char *msg, char *command, int code)
{
	print_error(msg, command);
	termios_restore_ctrl();
	exit(code);
}

void	print_error(char *msg, char *command)
{
	char	*base;

	if (command)
		base = ft_strjoin("Hérishell: ", command);
	else
		base = ft_strjoin("Hérishell: ", "unknown");
	if (errno && !msg)
	{
		g_glob.error = 1;
		perror(base);
	}
	else
	{
		ft_putstr_fd(base, 2);
		ft_putstr_fd(": ", 2);
		ft_putstr_fd(msg, 2);
		ft_putchar_fd('\n', 2);
	}
	free(base);
}
