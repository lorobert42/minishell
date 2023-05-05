/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exit.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lorobert <marvin@42lausanne.ch>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/19 09:22:18 by lorobert          #+#    #+#             */
/*   Updated: 2023/05/05 14:55:07 by lorobert         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

int	check_overflow(long long int base, long long int new, int sign)
{
	if (sign == 1)
	{
		if (LLONG_MAX / 10 < base)
			return (1);
		base *= 10;
		if (LLONG_MAX - base < new)
			return (1);
	}
	else
	{
		if (LLONG_MIN / 10 > base)
			return (1);
		base *= 10;
		if (LLONG_MIN - base > new * sign)
			return (1);
	}
	return (0);
}

long long int	ft_atoui(const char *str, int *overflow)
{
	int				sign;
	long long int	res;
	int				i;

	res = 0;
	sign = 1;
	i = 0;
	while (str[i] && ft_isspace(str[i]))
		i++;
	if (str[i] == '-' || str[i] == '+')
	{
		if (str[i++] == '-')
			sign = -1;
	}
	while (str[i] && str[i] >= '0' && str[i] <= '9')
	{
		*overflow = check_overflow(res, (long long int)str[i] - '0', sign);
		res *= 10;
		res += (str[i++] - '0') * sign;
	}
	return (res);
}

void	exit_error(t_data *data)
{
	print_error("numeric argument required", "exit");
	restore_stdio(data);
	exit(255);
}

void	check_digit(char **args, t_data *data)
{
	int	i;

	if (!ft_isspace(args[1][0]) && args[1][0] != '+' && args[1][0] != '-' && \
		!ft_isdigit(args[1][0]))
		exit_error(data);
	if ((args[1][0] == '+' || args[1][0] == '-') && !args[1][1])
		exit_error(data);
	i = 1;
	while (ft_isspace(args[1][i]))
		i++;
	while (args[1][i])
	{
		if (!ft_isdigit(args[1][i]))
			break ;
		i++;
	}
	while (ft_isspace(args[1][i]))
		i++;
	if (args[1][i])
		exit_error(data);
}

int	ft_exit(char **args, t_data *data)
{
	long long int	i;
	int				overflow;

	if (!args[1])
	{
		restore_stdio(data);
		exit(g_glob.error % 256);
	}
	check_digit(args, data);
	if (args[1] && args[2])
	{
		g_glob.error = 1;
		print_error("too many arguments", "exit");
		return (0);
	}
	overflow = 0;
	i = ft_atoui(args[1], &overflow);
	if (overflow)
		exit_error(data);
	restore_stdio(data);
	exit(i % 256);
}
