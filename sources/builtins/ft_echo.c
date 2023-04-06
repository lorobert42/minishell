/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_echo.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lorobert <marvin@42lausanne.ch>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/10 09:40:38 by lorobert          #+#    #+#             */
/*   Updated: 2023/03/31 13:41:16 by lorobert         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

/*
Check if parameter `-n` is used.
Have to be `-` followed by any number of `n` and no other char.
*/
static int	is_n(char *arg)
{
	int	i;

	i = 0;
	if (arg[i] != '-')
		return (0);
	i++;
	while (arg[i] == 'n')
		i++;
	if (arg[i] != '\0')
		return (0);
	return (1);
}

/*
Print content of args on file descriptor fd.
If parameter `-n` is set, do not print '\n' at the end.
Multiple `-n` are possible.
*/
int	ft_echo(char **args)
{
	int	i;
	int	n;

	n = 0;
	i = 0;
	while (args[i] && is_n(args[i]))
	{
		n = 1;
		i++;
	}
	while (args[i])
	{
		ft_printf("%s", args[i]);
		if (args[i + 1] && args[i + 1][0] != '\0')
			ft_printf(" ");
		i++;
	}
	if (!n)
		ft_printf("\n");
	g_glob = 0;
	return (0);
}
