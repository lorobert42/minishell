/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_echo.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lorobert <marvin@42lausanne.ch>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/10 09:40:38 by lorobert          #+#    #+#             */
/*   Updated: 2023/02/11 09:33:13 by lorobert         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "stdbool.h"
#include "stdio.h"
#include "libft.h"

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

int	ft_echo(char **args, int fd)
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
		ft_putstr_fd(args[i], fd);
		if (args[i + 1] && args[i + 1][0] != '\0')
			ft_putchar_fd(' ', fd);
		i++;
	}
	if (!n)
		ft_putchar_fd('\n', fd);
	return (0);
}
