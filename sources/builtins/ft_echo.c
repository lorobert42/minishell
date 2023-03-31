/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_echo.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lorobert <marvin@42lausanne.ch>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/10 09:40:38 by lorobert          #+#    #+#             */
/*   Updated: 2023/03/31 10:19:34 by lorobert         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
Check if parameter `-n` is used.
Have to be `-` followed by any number of `n` and no other char.
*/
static bool	is_n(char *arg)
{
	int	i;

	i = 0;
	if (arg[i] != '-')
		return (false);
	i++;
	while (arg[i] == 'n')
		i++;
	if (arg[i] != '\0')
		return (false);
	return (true);
}

/*
Print content of args on file descriptor fd.
If parameter `-n` is set, do not print '\n' at the end.
Multiple `-n` are possible.
*/
int	ft_echo(char **args)
{
	int		i;
	bool	n;

	i = 0;
	while (args[i] && is_n(args[i]))
	{
		n = true;
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
	return (0);
}
