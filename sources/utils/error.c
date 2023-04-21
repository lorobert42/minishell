/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lorobert <marvin@42lausanne.ch>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/31 11:22:27 by afavre            #+#    #+#             */
/*   Updated: 2023/04/21 11:07:00 by lorobert         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void	print_error(char *msg, char *command)
{
	char	*base;

	base = ft_strjoin("Hérishell: ", command);
	if (errno)
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
