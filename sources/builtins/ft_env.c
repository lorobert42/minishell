/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_env.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lorobert <marvin@42lausanne.ch>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/11 09:45:05 by lorobert          #+#    #+#             */
/*   Updated: 2023/02/24 09:26:52 by lorobert         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

/*
Print the environment variables on file descriptor fd in the form
key=value, followed by '\n'.
*/
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
	ft_putchar('\n');
	return (0);
}
