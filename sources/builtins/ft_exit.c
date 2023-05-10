/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exit.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lorobert <marvin@42lausanne.ch>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/19 09:22:18 by lorobert          #+#    #+#             */
/*   Updated: 2023/05/10 10:13:52 by lorobert         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void	exit_error(t_data *data)
{
	print_error("numeric argument required", "exit");
	termios_restore_ctrl();
	restore_stdio(data);
	exit(255);
}

int	check_overflow(char *nbr, char *max, char *min, t_data *data)
{
	int	i;

	if (nbr[0] == '+' || ft_isdigit(nbr[0]))
	{
		i = 0;
		if (nbr[0] == '+')
			i = 1;
		while (nbr[i])
		{
			if (nbr[i] > max[i])
				exit_error(data);
			i++;
		}
	}
	else
	{
		i = 1;
		while (nbr[i])
		{
			if (nbr[i] > min[i])
				exit_error(data);
			i++;
		}
	}
	return (0);
}

long long int	ft_atoui(const char *str)
{
	int				sign;
	long long int	res;
	int				i;

	res = 0;
	sign = 1;
	i = 0;
	if (str[i] == '-' || str[i] == '+')
	{
		if (str[i++] == '-')
			sign = -1;
	}
	while (str[i] && str[i] >= '0' && str[i] <= '9')
	{
		res *= 10;
		res += (str[i++] - '0') * sign;
	}
	return (res);
}

void	check_digit(char *args, t_data *data)
{
	int	i;

	if (args[0] != '+' && args[0] != '-' && !ft_isdigit(args[0]))
		exit_error(data);
	if ((args[0] == '+' || args[0] == '-') && !args[1])
		exit_error(data);
	i = 1;
	while (args[i])
	{
		if (!ft_isdigit(args[i]))
			break ;
		i++;
	}
	if (args[i])
		exit_error(data);
}

int	ft_exit(char **args, t_data *data)
{
	long long int	i;
	char			*nb;

	if (!args[1])
	{
		restore_stdio(data);
		termios_restore_ctrl();
		exit(g_glob.error % 256);
	}
	nb = ft_strtrim(args[1], "\x09\x0a\x0b\x0c\x0d ");
	check_digit(nb, data);
	nb = remove_zero(nb);
	if (ft_strlen(nb) >= 19)
		check_overflow(nb, "9223372036854775807", "-9223372036854775808", data);
	if (args[1] && args[2])
	{
		g_glob.error = 1;
		print_error("too many arguments", "exit");
		return (0);
	}
	i = ft_atoui(nb);
	restore_stdio(data);
	termios_restore_ctrl();
	exit(i % 256);
}
