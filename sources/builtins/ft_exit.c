/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exit.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lorobert <marvin@42lausanne.ch>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/19 09:22:18 by lorobert          #+#    #+#             */
/*   Updated: 2023/04/19 10:03:47 by lorobert         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

int	ft_exit(char **args)
{
	int	i;

	if (args[1] && args[2])
	{
		g_glob.error = 1;
		print_error("too many arguments", "exit");
		return (0);
	}
	if (!args[1])
		exit(g_glob.error);
	i = 0;
	while (args[1][i])
	{
		if (!ft_isdigit(args[1][i]))
		{
			print_error("numeric argument required", "exit");
			exit(255);
		}
		i++;
	}
	i = ft_atoi(args[1]);
	exit(i);
}
