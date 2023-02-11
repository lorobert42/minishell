/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_env.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lorobert <marvin@42lausanne.ch>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/11 09:45:05 by lorobert          #+#    #+#             */
/*   Updated: 2023/02/11 09:49:56 by lorobert         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_env(char **env, int fd)
{
	int	i;

	i = 0;
	while (env[i])
	{
		ft_putstr_fd(env[i], fd);
		if (env[i + 1])
			ft_putchar_fd('\n', fd);
		i++;
	}
	return (0);
}
