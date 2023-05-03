/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_echo.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lorobert <marvin@42lausanne.ch>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/10 09:40:38 by lorobert          #+#    #+#             */
/*   Updated: 2023/05/03 10:57:37 by lorobert         ###   ########.fr       */
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
	if (arg[i] != 'n')
		return (0);
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

void	print_home(t_data *data)
{
	char	**tmp;

	tmp = ft_split(ft_getenv(data->env, "HOME"), '=');
	ft_printf("%s", tmp[1]);
	clear_split(tmp);
}

int	ft_echo(t_data *data, char **args)
{
	int		i;
	int		n;

	n = 0;
	i = 0;
	while (args[i] && is_n(args[i]))
	{
		n = 1;
		i++;
	}
	while (args[i])
	{
		if (args[i][0] == '~')
			print_home(data);
		else
			ft_printf("%s", args[i]);
		if (args[i + 1])
			ft_printf(" ");
		i++;
	}
	if (!n)
		ft_printf("\n");
	g_glob.error = 0;
	return (0);
}
