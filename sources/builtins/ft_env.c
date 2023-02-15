/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_env.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lorobert <marvin@42lausanne.ch>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/11 09:45:05 by lorobert          #+#    #+#             */
/*   Updated: 2023/02/15 16:54:54 by lorobert         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_env(t_env *env, int fd)
{
	while (env)
	{
		ft_putstr_fd(env->key, fd);
		ft_putchar_fd('=', fd);
		ft_putstr_fd(env->value, fd);
		if (env->next)
			ft_putchar_fd('\n', fd);
		env = env->next;
	}
	return (0);
}
